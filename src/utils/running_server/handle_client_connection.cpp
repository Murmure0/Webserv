#include "../../../includes/webserv.hpp"
#include "../../server/webserv.hpp"

int webserv::accept_new_connection(int server_fd, sockaddr_in sockaddr)
{
	char buff[16];
	char buff_b[30];
	unsigned long addrlen = sizeof(sockaddr);
	int connection = accept(server_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
	if (connection < 0)
	{
		std::cout << "Failed to grab connection." << std::endl;
		return -1;
	}

	inet_ntop(AF_INET, &(sockaddr.sin_addr.s_addr), buff, INET_ADDRSTRLEN);
	if (!buff[0])
	{
		inet_ntop(AF_INET6, &(sockaddr.sin_addr.s_addr), buff_b, INET6_ADDRSTRLEN);
		_addr_ip = (std::string)buff_b;
	}
	else
		_addr_ip = (std::string)buff;
	return connection;
}

/*
function that handle all sockets
*/
int webserv::handle_client_connection(void)
{
	fd_set current_sockets;
	fd_set ready_read_sockets;
	fd_set ready_write_sockets;

	int ret;

	std::map<int, request> open_requests;
	std::map<int, responce> open_responces;

	FD_ZERO(&current_sockets);

	// ADD server socket to the current set of fd
	for (std::vector<listen_socket>::iterator i = _listen_sockets.begin(); i != _listen_sockets.end(); i++)
	{
		FD_SET((*i).get_fd(), &current_sockets);
	}

	// handling client connection
	while (true)
	{
		// select() is destructive, we're keeping the fd we're following in current_socket
		// and selecting from ready_sockets;
		ready_read_sockets = current_sockets;

		FD_ZERO(&ready_write_sockets);
		// add open responce to ready write sockets.
		for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
			FD_SET((*i).first, &ready_write_sockets);

		// struct timeval tv used for the timeout in select()
		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		/* select() examines the I/O descriptor sets whose addresses are passed in
		  readfds and writefds to see if some of their descriptors are ready for readin or are ready for writing
		  On return, select() replaces the given descriptor sets with subsets consisting of those descriptors that are ready for the requested operation.
		  select() returns the total number of ready descriptors in all the sets. */
		ret = select(FD_SETSIZE, &ready_read_sockets, &ready_write_sockets, NULL, &tv);

		// Peut etre simplifiée :
		if (ret < 0 || ret == 0) // error or timeout
		{
			if (ret < 0)
			{
				// creat the error strings
				for (std::map<int, request>::iterator i = open_requests.begin(); i != open_requests.end(); i++)
				{
					std::ifstream infile("./default_error_pages/500.html");
					std::string str_status = "500 Internal Server Error";

					std::stringstream ss;
					std::string str_resp;
					ss << infile.rdbuf();

					str_resp = "HTTP/1.1 " + str_status + "\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: text/html" + "\r\n\r\n" + ss.str() + "\r\n";
					infile.close();
					int len = str_resp.size();
					send((*i).first, (char *)str_resp.c_str(), len, 0);
					close((*i).first);
				}
			}
			else
			{
				for (std::map<int, request>::iterator i = open_requests.begin(); i != open_requests.end(); i++)
				{
					std::ifstream infile("./default_error_pages/408.html");
					std::string str_status = "408 Request Timeout";

					std::stringstream ss;
					std::string str_resp;
					ss << infile.rdbuf();

					str_resp = "HTTP/1.1 " + str_status + "\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: text/html" + "\r\n\r\n" + ss.str() + "\r\n";
					infile.close();
					int len = str_resp.size();
					send((*i).first, (char *)str_resp.c_str(), len, 0);
					close((*i).first);
				}
			}
			// close open_responces
			for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
			{
				close((*i).first);
			}
			open_responces.erase(open_responces.begin(), open_responces.end());
			// close open requests
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

		// /!\/!\/!\/!\ Zone en chantier :
		// loop on open_responces to send a small part of the response to each client simultaneously
		for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
		{
			if (FD_ISSET((*i).first, &ready_write_sockets))
			{

				// // save in the responce. Once save don't call anymore
				std::string str_resp = (*i).second.geterate_responce();
				(*i).second.set_responce(str_resp);

				str_resp = (*i).second.cuted_responce();
				int len = str_resp.size();

				// sending to client :
				// call new function in responce to get BUFFERSIZE each time
				send((*i).first, str_resp.c_str(), len, 0);

				// erase responce
				if ((*i).second.is_sent())
				{
					open_responces.erase(i);
					break;
				}
			}
		}

		// loop in open requests and fill in all of them
		for (std::map<int, request>::iterator i = open_requests.begin(); i != open_requests.end(); i++)
		{
			if (FD_ISSET((*i).first, &ready_read_sockets))
			{
				int ret = (*i).second.read_and_append((*i).first);
				if (ret < 0)
				{
					std::cout << "need close" << std::endl;
					open_requests.erase(i);
					open_responces.erase((*i).first);
					FD_CLR((*i).first, &current_sockets);
					close((*i).first);
					break;
				}
				if ((*i).second.is_completed())
				{
					open_responces[(*i).first] = responce((*i).second.get_header(), (*i).second.get_body(), (*i).second.get_addr_ip(), (*i).second.get_content_size(), get_mime(), generate_config((*i).second.get_port_location(), (*i).second.get_path(), (*i).second.get_header()));
					open_requests[(*i).first].clear();
					break;
				}
			}
		}

		// loop in listen sockets which are the main sockets
		for (std::vector<listen_socket>::iterator i = _listen_sockets.begin(); i != _listen_sockets.end(); i++)
		{
			// if socket ready create socket
			if (FD_ISSET((*i).get_fd(), &ready_read_sockets))
			{
				int client_socket = accept_new_connection((*i).get_fd(), (*i).get_addr());
				open_requests[client_socket] = request(this->_addr_ip);
				FD_SET(client_socket, &current_sockets);
			}
		}
	}
	// CTRL +C :
	exit(EXIT_SUCCESS);
}
