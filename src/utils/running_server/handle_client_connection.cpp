#include "../../../includes/webserv.hpp"
#include "../../server/webserv.hpp"

int webserv::accept_new_connection(int server_fd, sockaddr_in sockaddr)
{
	unsigned long addrlen = sizeof(sockaddr);
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
	// Read from the connection : here will be Parsing client response

	request req;

	char buffer[4096];
	size_t bytes_read = 4096;
	std::string buff;

	while (buff.find("\r\n\r\n") == std::string::npos && bytes_read >= 4095)
	{
		bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
		buffer[bytes_read] = 0;
		buff += std::string(buffer, bytes_read);
	}

	// req.config(buff.substr(0, buff.find("\r\n\r\n")));
	buff = buff.substr(buff.find("\r\n\r\n") + 4);

	char body_buffer[65536];
	bytes_read = bytes_read == 4095 ? 65536 : 0;
	while (bytes_read >= 65535)
	{
		bytes_read = recv(client_socket, body_buffer, sizeof(body_buffer) - 1, 0);
		buffer[bytes_read] = 0;
		buff += std::string(buffer, bytes_read);
	}

	std::cout << buff.size() << std::endl;

	// std::cout << "The request message was: " << buff.find("\r\n\r\n") << "  " << bytes_read;
	//  ici commence l'utilisation de notre classe server
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

int webserv::handle_client_connection(void)
{
	// J'ai tout vu la dedans : https://www.youtube.com/watch?v=Y6pFtgRdUts&t=1s

	// Initialize var & macro for using select() later
	fd_set current_sockets;
	fd_set ready_read_sockets;
	fd_set ready_write_sockets;

	int ret;

	std::map<int, request> open_requests;
	std::map<int, responce> open_responces;

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
		ready_read_sockets = current_sockets;

		FD_ZERO(&ready_write_sockets);
		for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
			FD_SET((*i).first, &ready_write_sockets);

		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		ret = select(FD_SETSIZE, &ready_read_sockets, &ready_write_sockets, NULL, &tv);

		if (ret < 0)
		{
			std::cout << "HoNo, select failed D:" << std::endl;
			exit(1);
		}
		else if (ret == 0)
		{
			// std::cout << &ready_read_sockets << std::endl;
			for (std::map<int, request>::iterator i = open_requests.begin(); i != open_requests.end(); i++)
			{
				std::ifstream infile("./default_error_pages/408.html");
				std::stringstream ss;
				std::string str_resp;

				ss << infile.rdbuf();

				// adding the minimal http header-ever to the file content:
				str_resp = "HTTP/1.1 408 Request Timeout\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: text/html" + "\r\n\r\n" + ss.str() + "\r\n";
				infile.close();

				int len = str_resp.size();
				send((*i).first, (char *)str_resp.c_str(), len, 0);
			}
			for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
			{
				close((*i).first);
			}
			open_responces.erase(open_responces.begin(), open_responces.end());
			for (std::map<int, request>::iterator i = open_requests.begin(); i != open_requests.end(); i++)
			{
				if (FD_ISSET((*i).first, &current_sockets))
				{
					FD_CLR((*i).first, &current_sockets);
				}
				close((*i).first);
			}
			open_requests.erase(open_requests.begin(), open_requests.end());
		}

		// wait for, and eventually accept and handle an incoming connection

		for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
		{
			if (FD_ISSET((*i).first, &ready_write_sockets))
			{
				/* working but not exactly how it was required, page img not ok for big img, ok for small ones */

				static std::string str_resp;
				if (str_resp.size() == 0)
					 str_resp = (*i).second.geterate_responce();
		
				int len = str_resp.size();
				std::cout << "reponse size = " << len << "|" << std::endl;

				while (str_resp.size() != 0)
				{
					std::string str_cut = str_resp.substr(0, BUFFER_SIZE);
					int len_cut = str_cut.size();
					str_resp.erase(0, BUFFER_SIZE);
					std::cout << "sent data size : " << len_cut << std::endl;
					send((*i).first, (char *)str_cut.c_str(), len_cut, 0);
				}

				open_responces.erase(i);
				close((*i).first);
				break;


				/* Solution lente, page img non fonctionnelle  */

				// static std::string str_resp;
				// if (str_resp.size() == 0)
				// 	 str_resp = (*i).second.geterate_responce();
		
				// int len = str_resp.size();
				// //std::cout << "reponse size = " << len << "|" << std::endl;

				// if (str_resp.size() != 0)
				// {
				// 	std::string str_cut = str_resp.substr(0, BUFFER_SIZE);
				// 	int len_cut = str_cut.size();
				// 	str_resp.erase(0, BUFFER_SIZE);
				// 	//std::cout << "sent data size : " << len_cut << std::endl;
				// 	send((*i).first, (char *)str_cut.c_str(), len_cut, 0);
				// }

				// open_responces.erase(i);
				// close((*i).first);
				// break; 



				/* ancienne version : petit img charge, pas la grande*/ 
				// std::string str_resp = (*i).second.geterate_responce();

				// int len = str_resp.size();
				// send((*i).first, (char *)str_resp.c_str(), len, 0);

				// open_responces.erase(i);
				// close((*i).first);
				// break; 
			}
		}

		for (std::map<int, request>::iterator i = open_requests.begin(); i != open_requests.end(); i++)
		{
			if (FD_ISSET((*i).first, &ready_read_sockets))
			{
				(*i).second.read_and_append((*i).first);
				if ((*i).second.is_completed())
				{
					open_responces[(*i).first] = responce((*i).second.get_header(), (*i).second.get_body(), get_mime(), generate_config((*i).second.get_port_location(), (*i).second.get_path()));
					FD_CLR((*i).first, &current_sockets);
					open_requests.erase(i);
					break;
				}
			}
		}

		for (std::vector<listen_socket>::iterator i = _listen_sockets.begin(); i != _listen_sockets.end(); i++)
		{
			if (FD_ISSET((*i).get_fd(), &ready_read_sockets))
			{
				int client_socket = accept_new_connection((*i).get_fd(), (*i).get_addr());
				open_requests[client_socket] = request();
				FD_SET(client_socket, &current_sockets);
			}
		}
	}
	// CTRL +C :
	exit(EXIT_SUCCESS);
}