#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <thread>

#include "serversocket.h"

bool is_running = true;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
	size_t buffer_len = 8192;
	char buffer[buffer_len];

	auto server = csocket::ServerSocket();

    std::thread::id this_id = std::this_thread::get_id();
	std::cout << "main: " << this_id << std::endl;

	if (server.listen("", 4992)) {
		std::cout << "listening...\n";

		while (is_running) {
			csocket::Socket client(*std::move(server.accept()));

			std::cout << "accept:"  << "\n";

			while (client.is_connected()) {
				std::cout << "waiting for data\n";
				auto bytes = client.receive(&buffer, buffer_len);

				std::string msg(buffer, bytes);
				std::cout << msg;
				client.send(msg.c_str(), msg.length());
			}

			client.close();
		}
	}


	return 0;
}
