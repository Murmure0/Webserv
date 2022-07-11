
#include "server/webserv.hpp"

int main(int argc, char **argv) {

	if (argc != 2)
	{
		return;
	}
	

	webserv ws;

	ws.config(argv[1]);

}