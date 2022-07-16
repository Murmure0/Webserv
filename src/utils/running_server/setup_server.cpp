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

	//WORKING ON SELECT BEFORE TRYING / infinite-loop 
	// /* Allow non-blocking connections, when we will have much more connections */
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

//essais comm


/*
	my basics Reminders :

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