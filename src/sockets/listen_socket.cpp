

#include "listen_socket.hpp"

listen_socket::listen_socket(void)
{
	// unused
}

listen_socket::listen_socket(int port) : _port(port)
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&_addr, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);

	int backlog = 10;

	if (_sockfd == -1)
	{
		std::cout << "Failed to create socket." << std::endl;
	}

	/* Allow tu reuse socket previously bind */
	const int enable = 1;
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		std::cout << "Failed to set socket option." << std::endl;
	}

	// WORKING ON SELECT BEFORE TRYING / infinite-loop
	//  /* Allow non-blocking connections, when we will have much more connections */
	//  if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0){
	//  	std::cout << "Failed to set the socket as unblocking." << std::endl;
	//  	return -1;
	//  }

	/* Connect the stream socket (socketfd) to the port listened by the server*/
	if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		std::cout << "Failed to bind to port " << port << std::endl;
	}

	/* Start listening. Hold at most backlog connections in the queue */
	if (listen(_sockfd, backlog) < 0)
	{
		std::cout << "Failed to listen on socket." << std::endl;
	}
}

listen_socket::~listen_socket(void)
{
}

listen_socket::listen_socket(listen_socket const &to_copy) : _port(to_copy._port), _sockfd(to_copy._sockfd), _addr(to_copy._addr) {}

int listen_socket::get_fd(void) const
{
	return _sockfd;
}

sockaddr_in listen_socket::get_addr(void) const
{
	return _addr;
}