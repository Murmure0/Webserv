#include "../../../includes/webserv.hpp"
#include "../../server/webserv.hpp"

int webserv::setup_server(int port, int backlog, sockaddr_in sockaddr)
{

	/* Creat a stream socket in the Internet domain */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cout << "Failed to create socket." << std::endl;
		return -1;
	}

	/* Allow tu reuse socket previously bind */
	const int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		std::cout << "Failed to set socket option." << std::endl;
		return -1;
	}

	// /* Allow non-blocking connections, when we will have much more connections */
	//WORKING ON SELECT BEFORE TRYING
	// if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0){
	// 	std::cout << "Failed to set the socket as unblocking." << std::endl;
	// 	return -1;
	// }
	
	/* Connect the stream socket (socketfd) to the port listened by the server*/
	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		std::cout << "Failed to bind to port " << port << std::endl;
		return -1;
	}

	/* Start listening. Hold at most backlog connections in the queue */
	if (listen(sockfd, backlog) < 0) {
		std::cout << "Failed to listen on socket." << std::endl;
		return -1;
	}

	return sockfd;
}

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

	fflush(stdout);

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


/*
	Reminder :

	someClass n = 2;
	get a pointer on n -> someClass *ptr = &n;
	get a reference on n -> someClass &ref = n; <- no need to precise you want the reference on the right side, it's automatic
*/

/*
	class someClass
	{
		public :
			int n;
			void set_n(int x) {this->n = x;}
			static void set_val(int x, someClass &myClass) { myClass.n = x;}
	}

	someClass myClass;
	myClass.set_n(4);
	someClass::set_val(4, myClass);
*/