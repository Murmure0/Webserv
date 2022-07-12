

#ifndef WEBSERV_H
#define WEBSERV_H

#include <string>
#include <iostream>
#include <map>
#include "../../includes/webserv.hpp"
#include "server.hpp"

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

	class ServerInitFailed : public std::exception{
		public:
			virtual const char* what() const throw()
			{
				return("Server initialisation failed.");
			}
	};


private:
	std::map<std::string, server> servers;
	std::map<std::string, server> first_on_port;
};

#endif // WEBSERV_H
