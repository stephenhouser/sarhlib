#include <iostream>

#include "tcpnet.h"

bool is_running = false;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

    std::thread::id this_id = std::this_thread::get_id();
	std::cout << "main: " << this_id << std::endl;

	auto client = tcpnet::TCPClient();
	if (client.connect("127.0.0.1", 4992)) {		
		is_running = true;
		while (is_running) {
			auto message = *std::move(client.recv_q.pop());
			std::cout << "RECV(" << this_id << "):" << message << std::endl;

			if (message == "quit") {
				break;
			}

			client.send_q.push(message);
		}
	}

	std::cout << "terminating..." << std::endl;
	client.disconnect();
}