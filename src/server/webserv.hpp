

#ifndef WEBSERV_H
#define WEBSERV_H

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

	void check_config(std::string config_file);
	void check_error(std::string reason);

	void run(void);
	void close_sockets(void);

	/* Used in run : */
	static int setup_server(int port, int backlog, sockaddr_in sockaddr);
	int handle_client_connection(void);
	int accept_new_connection(int server_fd, sockaddr_in sockaddr);

	class BadConfig : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("server initialisation failed");
		}
	};

	/*
	this function will generate the config structure used by the responce class
	*/
	t_responce_config generate_config(std::string host, std::string path, std::string header);
	std::map<std::string, std::string> *get_mime(void);

private:
	std::map<std::string, server> servers;
	std::map<std::string, std::string> servers_name_to_server;
	std::vector<listen_socket> _listen_sockets;
	std::map<std::string, std::string> mime;
	std::string _addr_ip;
};

#endif // WEBSERV_H
