

#include "listen_socket.hpp"

listen_socket::listen_socket(void)
{
	// unused
}

/*
setup the socket by creating one and bind it on the given port
*/
listen_socket::listen_socket(int port) : _port(port)
{

	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0)
	{
		std::cout << "Initialisation socket failed." << std::endl;
		throw listen_socket::ServerInitFailed();
	}
	bzero(&_addr, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);

	int backlog = 100;

	/* Allow tu reuse socket previously bind */
	const int enable = 1;
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		std::cout << "Failed to set socket option." << std::endl;
		throw listen_socket::ServerInitFailed();
	}

	// WORKING ON SELECT BEFORE TRYING / risk : infinite-loop
	/* Allow non-blocking connections, when we will have much more connections */
	if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "Failed to set the socket as unblocking." << std::endl;
		throw listen_socket::ServerInitFailed();
	}

	/* Connect the stream socket (socketfd) to the port listened by the server*/
	if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		std::cout << "Failed to bind to port " << port << std::endl;
		throw listen_socket::ServerInitFailed();
	}

	/* Start listening. Hold at most backlog connections in the queue */
	if (listen(_sockfd, backlog) < 0)
	{
		std::cout << "Failed to listen on socket." << std::endl;
		throw listen_socket::ServerInitFailed();
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
