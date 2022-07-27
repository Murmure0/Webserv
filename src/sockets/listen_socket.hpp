

#ifndef LISTEN_SOCKET_H
#define LISTEN_SOCKET_H

#include "../../includes/webserv.hpp"

class listen_socket
{
public:
	listen_socket(void);
	listen_socket(int port);
	~listen_socket(void);
	listen_socket(listen_socket const &copy);
	listen_socket &operator=(listen_socket const &rhs);

	int get_fd(void) const;
	sockaddr_in get_addr(void) const;

	class ServerInitFailed : public std::exception
			{
			public:
				virtual const char *what() const throw()
				{
					return ("Server initialisation failed.");
				}
			};

private:
	int _port;
	int _sockfd;
	sockaddr_in _addr;
};

#endif // LISTEN_SOCKET_H
