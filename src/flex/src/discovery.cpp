#include "flex/discovery.h"

namespace flex {
	//using discovery_callback_fn = void(*)(Radio);

	void Discovery::start() {
		_active = true;
	}

	void Discovery::stop() {
		_active = false;
	}

	void Discovery::receive() {
		// this is the receive loop.
		while (_active) {
			/*
			packet = udp.receive
			check sanity of packet
			process_vita_discovery_packet(new vitadiscovery(buffer))
			*/
		}
	}

	void Discovery::process_vita_discovery_packet(vita::VitaDiscoveryPacket &packet) {
		Radio radio;
		//parse discovery, set radio parameters
		// for kv in args
		//	...

		//std::vector<GUIClients> gui_clients = parse_gui_clients_discovery(...)
		// radio.gui_clients = gui_clients

		// Notify handlers
		on_radio_discovered(radio);
	}

	std::vector<GUIClient> Discovery::parse_gui_clients_discovery(
		std::string &programs_csv,
		std::string &stations_csv,
		std::string &handles_csv
	) {
		std::vector<GUIClient> clients;
		return clients;
	}

	void Discovery::add_on_radio_discovered(discovery_callback_fn handler) {
		_discovery_handlers.push_back(handler);				
	}

	void Discovery::on_radio_discovered(Radio &radio) {
		for (auto handler : _discovery_handlers) {
			handler(radio);
		}
	}

}