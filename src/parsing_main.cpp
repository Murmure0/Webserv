#include "server/webserv.hpp"


webserv* send_ws(webserv* ws)
{
	static webserv* awesome_ws = ws;
	return awesome_ws;
}

void signal_handler(int signal_handle)
{
	std::cout << std::endl;
	std::cout << "Goodbye." << std::endl;
	std::cout << std::endl;

	send_ws(nullptr)->close_sockets();
	exit(signal_handle);
}

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		std::cout << "Don't forget the config file" << std::endl;
		return 0;
	}

	webserv ws;
	send_ws(&ws);
	std::signal(SIGINT, signal_handler);
	try {
		ws.config(argv[1]);
	}
	catch (listen_socket::ServerInitFailed &e) {
		std::cerr << e.what() << std ::endl; 
		ws.close_sockets();
		exit(1);
	}

	ws.print();

	ws.run(1);

	return 0;
}