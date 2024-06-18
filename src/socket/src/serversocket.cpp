#include "serversocket.h"

#include <netdb.h>
#include <unistd.h>

#include <cstring>

namespace sarh {
namespace socket {

ServerSocket::ServerSocket() : Socket() {
}

ServerSocket::~ServerSocket() {
}

bool ServerSocket::listen(const std::string &host, int port) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = _sock_type;
	hints.ai_flags = AI_PASSIVE;

	// Get host address into servinfo from hostname and hints
	struct addrinfo *server_info;
	std::string port_str = std::to_string(port);
	if (::getaddrinfo(host.c_str(), port_str.c_str(), &hints, &server_info) != 0) {
		return false;
	}

	struct addrinfo *address;
	for (address = server_info; address != NULL; address = address->ai_next) {
		_sock_fd = ::socket(address->ai_family, address->ai_socktype, address->ai_protocol);
		if (_sock_fd == -1) {
			perror("server: socket");
			continue;
		}

		int yes = 1;
		if (::setsockopt(_sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("server: sockopt");
			return false;
		}

		if (::bind(_sock_fd, address->ai_addr, address->ai_addrlen) == -1) {
			::close(_sock_fd);
			perror("server: bind");
			continue;
		}

		break;
	}

	if (address == NULL) {
		perror("server: failed to setup");
		freeaddrinfo(server_info);
		return false;
	}

	freeaddrinfo(server_info);

	if (address != NULL) {
		if (::listen(_sock_fd, _connection_backlog) == -1) {
			perror("server: listen");
			return false;
		}
	}

	return address != NULL;
}

std::unique_ptr<Socket> ServerSocket::accept() {
	if (is_connected()) {
		struct sockaddr_storage peer_addr;	// connector's address information
		socklen_t peer_addr_size = sizeof(peer_addr);
		int new_fd = ::accept(_sock_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
		if (new_fd == -1) {
			perror("accept");
			return nullptr;
		}

		return std::make_unique<Socket>(new_fd);
	}

	return nullptr;
}

}  // namespace socket
}  // namespace sarh