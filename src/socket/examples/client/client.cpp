#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include "tcpsocket.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
	auto client = sarh::socket::TCPClient();

	client.connect("127.0.0.1", 4992);
	while (client.is_connected()) {
		std::cout << "waiting for data\n";
		auto msg = client.receive();

		std::cout << *msg;

		client.send(*msg);
	}

	client.disconnect();

	return 0;
}