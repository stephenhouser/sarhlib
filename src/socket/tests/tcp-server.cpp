#include <SafeQueue.h>
#include <tcpnet.h>

#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

bool is_running = false;

void client_handler(std::unique_ptr<tcpnet::Socket> socket) {
	size_t buffer_size = 8192;
	uint8_t buffer[buffer_size];

	while (socket->is_connected()) {
		size_t bytes_read = (size_t)socket->receive(buffer, buffer_size);
		if (bytes_read) {
			std::string message((char *)buffer, bytes_read);

			std::cout << "RECV:[" << message << "]";
			socket->send(message.c_str(), message.length());

			memset(buffer, 0, (size_t)bytes_read);
		}
	}
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
	std::thread::id this_id = std::this_thread::get_id();
	std::cout << "main : " << this_id << std::endl;

	tcpnet::ServerSocket server;
	if (server.listen("", 4992)) {
		is_running = true;
		while (is_running) {
			auto socket = server.accept();
			if (socket) {
				client_handler(std::move(socket));
			}
		}
	}

	std::cout << "terminating..." << std::endl;
	server.close();
}