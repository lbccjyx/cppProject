#include "fileinit.h"
#include "radixsort.h"
#include "threadForCout.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>


typedef websocketpp::client<websocketpp::config::asio_client> WebSocketclient;

void on_message(websocketpp::connection_hdl, WebSocketclient::message_ptr msg) {
	std::cout << msg->get_payload() << std::endl;
}


int main() {

	WebSocketclient c;

	std::string uri = "ws://localhost:9002";

	try {
		// Set logging to be pretty verbose (everything except message payloads)
		c.set_access_channels(websocketpp::log::alevel::all);
		c.clear_access_channels(websocketpp::log::alevel::frame_payload);
		c.set_error_channels(websocketpp::log::elevel::all);

		// Initialize ASIO
		c.init_asio();

		// Register our message handler
		c.set_message_handler(&on_message);

		websocketpp::lib::error_code ec;
		WebSocketclient::connection_ptr con = c.get_connection(uri, ec);
		if (ec) {
			std::cout << "could not create connection because: " << ec.message() << std::endl;
			return 0;
		}

		// Note that connect here only requests a connection. No network messages are
		// exchanged until the event loop starts running in the next line.
		c.connect(con);

		// Start the ASIO io_service run loop
		// this will cause a single connection to be made to the server. c.run()
		// will exit when this connection is closed.
		c.run();
		con->send("Hello, world!");

	}
	catch (websocketpp::exception const& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}