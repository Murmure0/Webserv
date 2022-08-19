#include "server/webserv.hpp"

webserv *send_ws(webserv *ws)
{
	static webserv *awesome_ws = ws;
	return awesome_ws;
}

void signal_handler(int signal_handle)
{
	bye();

	send_ws(NULL)->close_sockets();
	exit(signal_handle);
}

int main(int argc, char **argv)
{
	webserv ws;
	send_ws(&ws);
	std::signal(SIGINT, signal_handler);
	try
	{
		if (argc != 2)
			ws.check_config("src/config/config_file.conf");
		else
			ws.check_config(argv[1]);
	}
	catch (webserv::BadConfig &e)
	{
		std::cerr << e.what() << std ::endl;
		exit(1);
	}
	try
	{
		if (argc != 2)
			ws.config("src/config/config_file.conf");
		else
			ws.config(argv[1]);
	}
	catch (listen_socket::ServerInitFailed &e)
	{
		std::cerr << e.what() << std ::endl;
		ws.close_sockets();
		exit(1);
	}

	// ws.print();
	welcome();
	ws.run();

	return 0;
}