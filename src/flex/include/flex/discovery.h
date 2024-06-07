#ifndef FLEX_DISCOVERY_H
#define FLEX_DISCOVERY_H

#include <string>
#include <vector>

#include "radio.h"
#include "gui_client.h"
#include "vita/vita_discovery.h"

namespace flex {

	using discovery_callback_fn = void(*)(Radio &);

	class Discovery {
		public:
			void start();
			void stop();

			void add_on_radio_discovered(discovery_callback_fn handler);

			// Test routines
			void fake_discovery(const char *name) {
				Radio radio;
				radio.name = name;
				on_radio_discovered(radio);
			}

		private:
			int _discovery_port { 4992 };
			// udpclient udp
			bool _active { false };			
			std::vector<discovery_callback_fn> _discovery_handlers;

			void receive();
			void process_vita_discovery_packet(vita::VitaDiscoveryPacket &packet);
			std::vector<GUIClient> parse_gui_clients_discovery(
					std::string &programs_csv,
					std::string &stations_csv,
					std::string &handles_csv
			);
			void on_radio_discovered(Radio &radio);

	};
}

#endif // FLEX_DISCOVERY_H