#include "../../../includes/webserv.hpp"
#include "../../server/webserv.hpp"


int webserv::accept_new_connection(int server_fd, sockaddr_in sockaddr)
{
	unsigned long addrlen = sizeof(sockaddr);
	int connection = accept(server_fd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if (connection < 0) {
		std::cout << "Failed to grab connection." << std::endl;
		return -1;
	}
	return connection;
}

void webserv::handle_connection(int client_socket, int server_fd)
{
	// Read from the connection : Parsing client response !

	char buffer[4096];
	size_t bytes_read;
	int msg_size = 0;
	
	 while((bytes_read = read(client_socket, buffer + msg_size, sizeof(buffer)-msg_size-1)))
	 {
		msg_size += bytes_read;
		if (msg_size > 4095 || buffer[msg_size-1] == '\n')
			break;
	 }
	 buffer[msg_size-1] = 0;
	std::cout << "The request message was: " << buffer;
	std::cout << std::endl;

	fflush(stdout);

	// Whatever the client is asking, giving the index.html, img not working, don't know why yet :

	std::ifstream infile("./website/ressources/index.html");
	if(!infile.good())
	{
		std::cout <<"Wrong filename."<< std::endl;
		return ;
	}
	else if (infile.peek() == EOF)
	{
		std::cout << "Empty file." << std::endl;
		return ;
	}
	std::stringstream ss;
	std::string str_resp;

	ss << infile.rdbuf();
	str_resp = "HTTP/1.1 200 OK\r\n\r\n" + ss.str() + "\r\n";

	int len = str_resp.size();

	send(client_socket, (char*)str_resp.c_str(), len, 0);

	infile.close();

	close(client_socket);
	return ;
}

int webserv::handle_client_connection(int server_fd, sockaddr_in sockaddr)
{
//initialize var & macro for select()
	fd_set current_sockets;
	fd_set ready_socket;

	FD_ZERO(&current_sockets);
	//ADD server socket to the current set of fd
	//should do it later for each server socket 
	FD_SET(server_fd, &current_sockets);


	// handling client connection :
	while(true)
	{
		//select() is destructive, we're keeping the fd we're following in current_socket 
		//and selecting from ready_socket;
		ready_socket = current_sockets;

		if(select(FD_SETSIZE, &ready_socket,  NULL, NULL, 0))
		{

		}

		//wait for, and eventually accept an incoming connection
		int client_socket = accept_new_connection(server_fd, sockaddr);
		//do what you want with the connection :
		handle_connection(client_socket, server_fd);
	}
}