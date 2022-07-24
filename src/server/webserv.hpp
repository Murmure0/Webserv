

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
	int handle_client_connection(void);
	static int accept_new_connection(int server_fd, sockaddr_in sockaddr);

	/*
	this function will generate the config structure used by the responce class
	*/
	t_responce_config generate_config(std::string host, std::string path)
	{
		server *selected = NULL;
		// if hostname match with server use this server. If not use defalt server with this port
		if (servers_name_to_server.find(host) != servers_name_to_server.end())
			selected = &servers[servers_name_to_server[host]];
		else
			selected = &servers[host.substr(host.find(":") + 1) + "_0"];

		// get location that match with path if exist
		location *loc = selected->get_location(path);
		t_responce_config config;
		config.url = path;
		if (loc)
		{
			// get config from server and overide it with location
			selected->config_responce(&config);
			loc->config_responce(&config);
			if (loc->have_root())
				config.path = complete_url(config.path, path.substr(loc->get_location_match().size()));
			else
				config.path = complete_url(config.path, path);
		}
		else
		{
			// get config from server
			selected->config_responce(&config);
			config.path += rtrim(path, "/");
		}
		std::cout << config.path << " " << config.root << " " << config.index << std::endl;
		// add index if exist
		if (compare_url(config.path, config.root) && config.index.size())
		{
			config.path = complete_url(config.path, config.index);
		}
		if (loc)
		{
			std::cout << "url: " << config.url << " | " << selected->get_id() + ":" + selected->get_server_name() << " | loc: " << loc->get_location_match() << " | " << config.path << std::endl;
		}
		else
		{
			std::cout << "url: " << config.url << " | " << selected->get_id() + ":" + selected->get_server_name() << " | alone | " << config.path << std::endl;
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
