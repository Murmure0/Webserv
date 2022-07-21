

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
	void close_fd(void);
	void close_sockets(void);

	static int setup_server(int port, int backlog, sockaddr_in sockaddr);
	static int handle_client_connection(int server_fd, sockaddr_in sockaddr);
	int handle_client_connection(void);
	static int accept_new_connection(int server_fd, sockaddr_in sockaddr);
	static void handle_connection(int client_socket);

	t_responce_config generate_config(std::string host, std::string path)
	{
		server *selected = NULL;
		if (servers_name_to_server.find(host) != servers_name_to_server.end())
		{
			selected = &servers[servers_name_to_server[host]];
		}
		else
		{
			selected = &servers[host.substr(host.find(":") + 1) + "_0"];
		}
		location *loc = selected->get_location(path);
		t_responce_config config;
		if (loc)
		{
			selected->config_responce(&config);
			loc->config_responce(&config);
			config.path += path.substr(loc->get_location_match().size());
		}
		else
		{
			selected->config_responce(&config);
			config.path += path;
		}
		return config;
	}

	std::map<std::string, std::string> *get_mime(void)
	{
		return &mime;
	};

private:
	std::map<std::string, server> servers;
	std::map<std::string, std::string> servers_name_to_server;
	std::vector<listen_socket> _listen_sockets;
	std::map<std::string, std::string> mime;
};

#endif // WEBSERV_H
