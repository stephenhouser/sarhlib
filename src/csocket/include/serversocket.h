//
// Created by Stephen Houser on 3/29/24.
//
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <memory>
#include <string>

#include "socket.h"

namespace csocket {
	
	class ServerSocket : public Socket {
		public:
			ServerSocket();
			~ServerSocket();

			bool listen(const std::string &host, int port);
			std::unique_ptr<Socket> accept();

		private:
			std::string _host {};
			//int _port {-1};
			int _connection_backlog {10};
	};
}

#endif // SERVERSOCKET_H
