#include "server/webserv.hpp"

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		return 0;
	}

	webserv ws;

	ws.config(argv[1]);

	ws.print();

	// ws.run();
	return 0;
}