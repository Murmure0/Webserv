#include "../../../includes/webserv.hpp"

int setup_server(int port, int backlog, sockaddr_in sockaddr)
{
	// exemple :
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cout << "Failed to create socket." << std::endl;
		return -1;
	}

	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		std::cout << "Failed to bind to port " << port << std::endl;
		return -1;
	}

	// // Start listening. Hold at most backlog connections in the queue
	if (listen(sockfd, backlog) < 0) {
		std::cout << "Failed to listen on socket." << std::endl;
		return -1;
	}

	return sockfd;

	// // Grab a connection from the queue

		
	return 0;
}

int accept_new_connection(int server_fd, sockaddr_in sockaddr)
{
	auto addrlen = sizeof(sockaddr);
	int connection = accept(server_fd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if (connection < 0) {
		std::cout << "Failed to grab connection." << std::endl;
		return -1;
	}
	return connection;
}

void handle_connection(int client_socket, int server_fd, int connection)
{
	// Read from the connection
	char buffer[100];
	auto bytesRead = read(connection, buffer, 100);
	std::cout << "The message was: " << buffer;

	// Send a message to the connection
	std::string response = "Good talking to you\n";
	send(connection, response.c_str(), response.size(), 0);

	// Close the connection
	close(connection);
}