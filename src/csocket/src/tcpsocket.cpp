#include <cstring>
#include "socket.h"
#include "tcpsocket.h"

using namespace csocket;

namespace tcpsocket {

    TCPQueue::TCPQueue() {
    }

	TCPQueue::TCPQueue(std::unique_ptr<Socket> socket) {
        if (socket) {
            _socket = std::move(socket);
            _start();
        }
    }

    TCPQueue::~TCPQueue() {
        disconnect();
    }

    bool TCPQueue::is_connected() {
        return _socket && _socket->is_connected();
    }

    bool TCPQueue::send(const std::string &message) {
        if (_socket) {
            _send_q.push(message);
            return true;
        }

        return false;
    }

    std::unique_ptr<std::string> TCPQueue::receive() {
        if (_socket) {
            return _recv_q.pop();
        }

        return nullptr;
    }

    void TCPQueue::disconnect() {
        if (_socket) {
            _socket->shutdown();
            _socket->close();
            _socket.release();
        }

        _stop();
    }

    void TCPQueue::_start() {
        _reader_thread = std::thread(&TCPQueue::_reader_thunk, this);
        _writer_thread = std::thread(&TCPQueue::_writer_thunk, this);
    }

    void TCPQueue::_stop() {
        if (_reader_thread.joinable()) {
            _reader_thread.join();
        }

        _send_q.push(static_cast<std::unique_ptr<std::string>>(nullptr));
        if (_writer_thread.joinable()) {
            _writer_thread.join();
        }        
    }

    void *TCPQueue::_reader_loop() {
        size_t offset {0};              // location in buffer to recevive to
        uint8_t buffer[_buffer_size];   // receive buffer
        memset(buffer, 0, _buffer_size);

        while (is_connected()) {
            size_t capacity = _buffer_size - offset - 1;
            ssize_t bytes_read = _socket->receive((buffer+offset), capacity);
            if (bytes_read == -1) {
                perror("receive");
                break;
            }

            if (bytes_read != 0) {
                offset += (size_t)bytes_read;
                if (buffer[offset-1] == _terminator) {
                    auto message = std::make_unique<std::string>((char *)buffer, offset);
                    _recv_q.push(std::move(message));

                    offset = 0;
                    memset(buffer, 0, _buffer_size);
                }
            }
        }

        return nullptr;
    }

    void *TCPQueue::_writer_loop() {
        while (is_connected()) {
            std::unique_ptr<std::string> message = _send_q.pop();
            if (message) {
                size_t message_length = message->length();
                ssize_t bytes_sent = _socket->send(message->c_str(), message->length());

                message.release();

                if ((size_t)bytes_sent != message_length) {
                    perror("send");
                    break;
                }
            }
        }

        return nullptr;
    }

    // *** TCPClient ***

    bool TCPClient::connect(const std::string &host, const int port) {
        if (!is_connected()) {
            _socket = std::make_unique<Socket>();
            if (_socket && _socket->connect(host, port)) {
                _host = host;
                _port = port;
                _start();
                return true;
            }
        }

        return false;
    }


    // *** TCPServer ***
/*
    bool TCPServer::listen(const std::string &host, const int port) {
        if (connected) {
            return false;
        }

        connected = _listen_socket(host, port);
        if (connected) {
            this->host = host;
            this->port = port;

            //_start();
        }

        return connected;
    }

    bool TCPServer::_listen_socket([[maybe_unused]] const std::string &host, int port) {
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        // Get host address into servinfo from hostname and hints
        struct addrinfo *server_info;
        std::string port_str = std::to_string(port);
        if (::getaddrinfo(NULL, port_str.c_str(), &hints, &server_info) != 0) {
            return false;
        }

        struct addrinfo *address;
        for (address= server_info; address != NULL; address = address->ai_next) {
            sock_fd = ::socket(address->ai_family, address->ai_socktype, address->ai_protocol);
            if (sock_fd == -1) {
                perror("server: socket");
                continue;
            }

            int yes = 1;
            if (::setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                perror("server: sockopt");
                return false;
            }

            if (::bind(sock_fd, address->ai_addr, address->ai_addrlen) == -1) {
                ::close(sock_fd);
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
            if (::listen(sock_fd, backlog) == -1) {
		        perror("server: listen");
		        return false;
	        }
        }

        return address != NULL;
    }

    std::unique_ptr<TCPBase> TCPServer::accept([[maybe_unused]] void (&handler)(tcpnet::TCPBase&)) {
        if (!connected) {
            return nullptr;
        }

        struct sockaddr_storage peer_addr; // connector's address information
        socklen_t peer_addr_size = sizeof(peer_addr);
        int new_fd = ::accept(sock_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
        if (new_fd == -1) {
            perror("accept");
            return nullptr;
        }

        return std::make_unique<TCPBase>(new_fd);
    }

    // get sockaddr, IPv4 or IPv6:
    void *get_in_addr(struct sockaddr *sa) {
        if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
*/
}