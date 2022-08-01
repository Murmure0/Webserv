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

		// add open responce to ready write sockets.
		FD_ZERO(&ready_write_sockets);
		for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
			FD_SET((*i).first, &ready_write_sockets);

		struct timeval tv;
		tv.tv_sec = 60;
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
			// handle times out
			// clear responces and send to them 408 error
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

		// wait for, and eventually accept and handle an incoming connection

		// loop on open_responces to send a small part of the response to each client
		for (std::map<int, responce>::iterator i = open_responces.begin(); i != open_responces.end(); i++)
		{
			if (FD_ISSET((*i).first, &ready_write_sockets))
			{

				/* first method :*/
				// save in the responce. Once save don't call anymore
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
					close((*i).first);
					FD_CLR((*i).first, &current_sockets);
					break;
				}
			}
		}

		// loop in open requests and fill in all of them
		for (std::map<int, request>::iterator i = open_requests.begin(); i != open_requests.end(); i++)
		{
			if (FD_ISSET((*i).first, &ready_read_sockets))
			{
				(*i).second.read_and_append((*i).first);
				if ((*i).second.is_completed())
				{
					open_responces[(*i).first] = responce((*i).second.get_header(), (*i).second.get_body(), get_mime(), generate_config((*i).second.get_port_location(), (*i).second.get_path(), (*i).second.get_header()));
					FD_CLR((*i).first, &current_sockets);
					open_requests.erase(i);
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
				open_requests[client_socket] = request();
				FD_SET(client_socket, &current_sockets);
			}
		}
	}
	// CTRL +C :
	exit(EXIT_SUCCESS);
}