#include "socket.h"

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>

namespace sarh {
namespace socket {

Socket::Socket() {
}

Socket::Socket(int fd) {
	_sock_fd = fd;
}

Socket::~Socket() {
	shutdown();
	close();
}

bool Socket::connect(const std::string &host, int port) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = _sock_type;

	// Get host address into servinfo from hostname and hints
	struct addrinfo *server_info;
	std::string port_str = std::to_string(port);
	if (::getaddrinfo(host.c_str(), port_str.c_str(), &hints, &server_info) != 0) {
		return false;
	}

	// loop through all the results and connect to the first we can
	struct addrinfo *address;
	for (address = server_info; address != NULL; address = address->ai_next) {
		_sock_fd = ::socket(address->ai_family, address->ai_socktype, address->ai_protocol);
		if (_sock_fd == -1) {
			perror("client: socket");
			continue;
		}

		if (::connect(_sock_fd, address->ai_addr, address->ai_addrlen) == -1) {
			::close(_sock_fd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (address == NULL) {
		perror("client: failed to connect");
		freeaddrinfo(server_info);
		return false;
	}

	freeaddrinfo(server_info);
	return address != NULL;
}

bool Socket::is_connected() {
	if (_sock_fd != -1) {
		int error_code;
		socklen_t error_code_size = sizeof(error_code);
		if (getsockopt(_sock_fd, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size) != -1) {
			return error_code == 0;
		}
	}

	return false;
}

ssize_t Socket::send(const void *buf, size_t len) {
	ssize_t bytes_sent = ::send(_sock_fd, buf, len, 0);
	return bytes_sent;
}

ssize_t Socket::receive(void *buf, size_t len) {
	ssize_t bytes_read = ::recv(_sock_fd, buf, len, 0);
	return bytes_read;
}

void Socket::shutdown() {
	if (_sock_fd != -1) {
		::shutdown(_sock_fd, SHUT_RDWR);
	}
}

void Socket::close() {
	if (_sock_fd != -1) {
		::close(_sock_fd);
		_sock_fd = -1;
	}
}

}  // namespace socket
}  // namespace sarh