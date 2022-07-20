

#ifndef WEBSERV_H
#define WEBSERV_H

#include <string>
#include <iostream>
#include "../../includes/webserv.hpp"
#include "server.hpp"
#include "../sockets/listen_socket.hpp"

class webserv
{
public:
	webserv(void);
	~webserv(void);
	webserv(webserv const &copy);
	webserv &operator=(webserv const &rhs);

	void print(void) const;

	void config(std::string config_file);
	void run(void);
	void run(int test);
	void close_fd(void);
	void close_sockets(void);

	static int setup_server(int port, int backlog, sockaddr_in sockaddr);
	static int handle_client_connection(int server_fd, sockaddr_in sockaddr);
	int handle_client_connection(void);
	static int accept_new_connection(int server_fd, sockaddr_in sockaddr);
	static void handle_connection(int client_socket);

private:
	std::map<std::string, server> servers;
	std::vector<listen_socket> _listen_sockets;
};

/*

4000_1
8888_1
8888_2
8888_3

map<string, string>
4040_localhost 4040_1

*/

#endif // WEBSERV_H
