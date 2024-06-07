
#include <iostream>
#include <string>
#include <cstring>
#include <memory>

#include <flex/radio.h>
#include <flex/discovery.h>

//	using discovery_callback_fn = void(*)(Radio &);

void radio_discovered(flex::Radio &radio) {
	std::cout << "Radio!" << radio.name << "\n";
}

int main(int argc, char **argv) {
	flex::Discovery discovery;

	discovery.add_on_radio_discovered(radio_discovered);
	discovery.fake_discovery("sample");

	return 0;
}