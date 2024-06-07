#include <iostream>
#include <string>
#include <cstring>
#include <memory>

#include "tcpsocket.h"

int main(int argc, char **argv) {
	auto client = tcpsocket::TCPClient();

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