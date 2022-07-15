

#include "webserv.hpp"

webserv::webserv(void)
{
}

webserv::~webserv(void)
{
	servers.clear();
}

webserv::webserv(webserv const &to_copy) {}

webserv &webserv::operator=(webserv const &rhs)
{
	return *this;
}

void webserv::print(void) const
{
	for (std::map<std::string, server>::const_iterator i = servers.begin(); i != servers.end(); i++)
	{
		(*i).second.print();
	}
}

void webserv::config(std::string config_file)
{
	std::string s = file_to_string(config_file);
	t_config m_c;
	t_config s_c;
	t_config l_c;

	bool m_i = true;
	bool s_i = true;
	bool l_i = true;

	while (!m_c.key.empty() || m_i)
	{
		m_i = false;
		m_c = get_next_variable(s);
		if (m_c.key == "server")
		{
			std::pair<std::string, server> pair;
			while (!s_c.key.empty() || s_i)
			{
				s_i = false;
				s_c = get_next_variable(m_c.value);

				if (s_c.key == "location")
				{
					std::pair<std::string, location> l_pair;
					l_pair.first = s_c.before_braquet;
					l_pair.second.set("location_match", s_c.before_braquet);
					while (!l_c.key.empty() || l_i)
					{
						l_i = false;
						l_c = get_next_variable(s_c.value);
						l_pair.second.set(l_c.key, l_c.value);
						if (s_c.value.length() > l_c.next_start)
							s_c.value = s_c.value.substr(l_c.next_start);
						else
							break;
					}
					pair.second.add_location(l_pair);
				}
				else
				{
					pair.second.set(s_c.key, s_c.value);
				}
				if (m_c.value.length() > s_c.next_start)
					m_c.value = m_c.value.substr(s_c.next_start);
				else
					break;
			}
			pair.first = pair.second.get_id() + "_" + std::to_string(servers.size());
			servers.insert(pair);
		}
		if (s.length() > m_c.next_start)
			s = s.substr(m_c.next_start);
		else
			break;
	}
}



void webserv::run(void)
{
	std::cout << "Server running : listening on port 8080 (test)" << std::endl;

	// server &server_one = this->servers.find("id_server")->second; //trouver les ports
	// std::string const &port_one = server_one.get_id();
	// int port_int = atoi(port_one.c_str());

	int port = 8080;
	int backlog = 10 ; //maximum length to which the queue of pending connections for sockfd may grow.
	
	// initialiser une struct sockaddr / port
	// // Listen to the port given on any address
	sockaddr_in sockaddr;
	bzero(&sockaddr, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(port); // htons is necessary to convert a number to
									// network byte order
	int server_fd= setup_server(port, backlog, sockaddr); //pour un seul serveur pour l'instant
	if(server_fd < 0) 
	{
		throw (ServerInitFailed());
	}

	// gerer connections clients:
	while(true)
	{
		//wait for, and eventually accept an incoming connection
		int client_socket = accept_new_connection(server_fd, sockaddr);
		//do what you want with the connection :
		handle_connection(client_socket, server_fd);
	}
	close(server_fd);
}
