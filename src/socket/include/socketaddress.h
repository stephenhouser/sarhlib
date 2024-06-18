//
// Created by Stephen Houser on 3/29/24.
//
#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H

#include <string>

namespace sarh {
namespace socket {

class SocketAddress {
	public:
		static SocketAddress *create_unresolved(std::string &host, int port);

		SocketAddress(std::string &host, int port);
		SocketAddress(int port);
		~SocketAddress();

		std::string get_address();
		std::string get_hostname();
		int get_port();

	private:
		std::string host;
		int port;
};

}  // namespace socket
}  // namespace sarh

#endif	// SOCKETADDRESS_H