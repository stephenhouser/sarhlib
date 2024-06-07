//
// Created by Stephen Houser on 3/29/24.
//
#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <string>
#include <thread>

#include "socket.h"
#include "serversocket.h"
#include "safequeue/safequeue.h"

using namespace csocket;

namespace tcpsocket {

	class TCPQueue {
		public:
			TCPQueue();
			TCPQueue(std::unique_ptr<Socket> socket);
			~TCPQueue();

			bool is_connected();

			bool send(const std::string &message);
			std::unique_ptr<std::string> receive();

			void disconnect();

		private:
			std::string _host {};
			int _port {};

			char _terminator {'\n'};
			safequeue::queue _recv_q {};
			safequeue::queue _send_q {};

			size_t _buffer_size {16384};
			std::unique_ptr<Socket> _socket {nullptr};
			
			void _start();
			void _stop();
			
			void *_reader_loop();
			std::thread _reader_thread {};
			static void *_reader_thunk(void *self) {
				return static_cast<TCPQueue *>(self)->_reader_loop();
			}

			void *_writer_loop();
			std::thread _writer_thread {};
			static void *_writer_thunk(void *self) {
				return static_cast<TCPQueue *>(self)->_writer_loop();
			}

		friend class TCPClient;
    };		


    class TCPClient : public TCPQueue {
		public:
			bool connect(const std::string &host, const int port);

		private:
			std::string _host;
			int _port;

			bool _connect_socket();
	};

/*
	class TCPServer : public TCPQueue {
		private:
			int backlog {10};

		public:
			bool listen(const std::string &host, const int port);
			std::unique_ptr<TCPQueue> accept(void (&handler)(tcpnet::TCPQueue&));

		private:
			bool _listen_socket(const std::string &host, const int port);
	};
*/
}

#endif // TCP_SOCKET_H