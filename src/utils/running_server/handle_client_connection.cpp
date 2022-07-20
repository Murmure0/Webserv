#include "../../../includes/webserv.hpp"
#include "../../server/webserv.hpp"

int webserv::accept_new_connection(int server_fd, sockaddr_in sockaddr)
{
	unsigned long addrlen = sizeof(sockaddr);
	std::cout << "///////////////" << std::endl;
	std::cout << "///////NEW////" << std::endl;
	std::cout << "///////////////" << std::endl;
	int connection = accept(server_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
	if (connection < 0)
	{
		std::cout << "Failed to grab connection." << std::endl;
		return -1;
	}
	return connection;
}

void webserv::handle_connection(int client_socket)
{
	// Read from the connection : here will be Parsing client response !

	char buffer[4096];
	size_t bytes_read;
	int msg_size = 0;

	while ((bytes_read = read(client_socket, buffer + msg_size, sizeof(buffer) - msg_size - 1)))
	{
		msg_size += bytes_read;
		if (msg_size > 4095 || buffer[msg_size - 1] == '\n')
			break;
	}
	buffer[msg_size - 1] = 0;
	std::cout << "The request message was: " << buffer;
	// ici commence l'utilisation de notre classe server
	std::cout << std::endl;

	fflush(stdout);

	// Whatever the client is asking, giving the content of index.html, img not working, don't know why yet :
	// opening and reading from the file like a N00b, don't hesitate to correct me :)

	std::ifstream infile("./website/ressources/index.html");
	if (!infile.good())
	{
		std::cout << "Wrong filename." << std::endl;
		return;
	}
	else if (infile.peek() == EOF)
	{
		std::cout << "Empty file." << std::endl;
		return;
	}
	std::stringstream ss;
	std::string str_resp;

	ss << infile.rdbuf();

	// adding the minimal http header-ever to the file content:
	str_resp = "HTTP/1.1 200 OK\r\n\r\n" + ss.str() + "\r\n";

	int len = str_resp.size();

	// sending to client :
	send(client_socket, (char *)str_resp.c_str(), len, 0);

	infile.close();
	close(client_socket);
	return;
}

int webserv::handle_client_connection(int server_fd, sockaddr_in sockaddr)
{
	// J'ai tout vu la dedans : https://www.youtube.com/watch?v=Y6pFtgRdUts&t=1s

	// Initialize var & macro for using select() later
	fd_set current_sockets;
	fd_set ready_sockets;

	FD_ZERO(&current_sockets);

	// ADD server socket to the current set of fd
	// Later : ADD all other server_fd
	FD_SET(server_fd, &current_sockets);

	// handling client connection :
	while (true)
	{
		// select() is destructive, we're keeping the fd we're following in current_socket
		// and selecting from ready_sockets;
		ready_sockets = current_sockets;

		if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, 0) < 0)
		{
			std::cout << "HoNo, select failed D:" << std::endl;
			exit(1);
		}
		std::cout << "Waiting for connections..." << std::endl;

		// wait for, and eventually accept and handle an incoming connection
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &ready_sockets))
			{
				if (i == server_fd)
				{
					int client_socket = accept_new_connection(server_fd, sockaddr);
					FD_SET(client_socket, &current_sockets);
				}
				else
				{
					// do what you want with the connection :
					handle_connection(i);
					FD_CLR(i, &current_sockets);
				}
			}
		}
	}
	// CTRL +C :
	exit(EXIT_SUCCESS);
}

std::vector<listen_socket>::iterator find(std::vector<listen_socket>::iterator begin, std::vector<listen_socket>::iterator end, int to_find)
{
	while (begin < end)
	{
		if ((*begin).get_fd() == to_find)
		{
			return begin;
		}
		begin++;
	}
	return end;
}

int webserv::handle_client_connection(void)
{
	// J'ai tout vu la dedans : https://www.youtube.com/watch?v=Y6pFtgRdUts&t=1s

	// Initialize var & macro for using select() later
	fd_set current_sockets;
	fd_set ready_sockets;
	int index;

	FD_ZERO(&current_sockets);

	// ADD server socket to the current set of fd
	// Later : ADD all other server_fd
	for (std::vector<listen_socket>::iterator i = _listen_sockets.begin(); i != _listen_sockets.end(); i++)
	{
		FD_SET((*i).get_fd(), &current_sockets);
	}

	// handling client connection :
	while (true)
	{
		// select() is destructive, we're keeping the fd we're following in current_socket
		// and selecting from ready_sockets;
		ready_sockets = current_sockets;

		if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, 0) < 0)
		{
			std::cout << "HoNo, select failed D:" << std::endl;
			exit(1);
		}
		std::cout << "Waiting for connections..." << std::endl;

		// wait for, and eventually accept and handle an incoming connection
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &ready_sockets))
			{
				std::vector<listen_socket>::iterator it = find(_listen_sockets.begin(), _listen_sockets.end(), i);
				if (it != _listen_sockets.end()) //on determine si un fd server a été interpelé par un client
				{
					int client_socket = accept_new_connection((*it).get_fd(), (*it).get_addr());
					FD_SET(client_socket, &current_sockets); //on ajoute le fd du client dans les currents sockets à surveiller par select
				}
				else
				{
					handle_connection(i); //on fait ce qu'on a a faire avec le client
					FD_CLR(i, &current_sockets); //on enleve le client socket des current_sockets une fois qu'on a terminé ce qu'on avait a faire avec lui
				}
			}
		}
	}
	// CTRL +C :
	exit(EXIT_SUCCESS);
}