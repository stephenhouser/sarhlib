//
// Created by Stephen Houser on 3/29/24.
//
#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

#include <string>

namespace sarh {
namespace socket {

class Socket {
	public:
		Socket();
		Socket(int fd);
		~Socket();

		ssize_t send(const void *buf, size_t len);
		ssize_t receive(void *buf, size_t len);

		void shutdown();
		void close();
		bool connect(const std::string &host, int port);
		bool is_connected();

	private:
		int _sock_fd{-1};
		int _sock_type{SOCK_STREAM};

		friend class ServerSocket;
};
}  // namespace csocket
}  // namespace sarh

#endif	// SSOCKET_H
