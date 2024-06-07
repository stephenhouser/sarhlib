
#include <iostream>
#include <string>
#include <cstring>
#include <memory>

#include <flex/discovery.h>

int main(int argc, char **argv) {
	flex::Discovery discovery;

	std::cout << "discover" << discovery.is_active() << "\n";


	return 0;
}