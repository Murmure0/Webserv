

#include "webserv.hpp"

webserv::webserv(void)
{
}

webserv::~webserv(void)
{
	close_sockets();
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
		std::cout << (*i).first << std::endl;
		(*i).second.print();
	}
}

void webserv::config(std::string config_file)
{
	std::string s = file_to_string(config_file);
	std::map<int, int> port_count;
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
			if (port_count.find(stoi(pair.second.get_id())) == port_count.end())
			{
				std::pair<int, int> port_pair(stoi(pair.second.get_id()), 0);
				listen_socket sock(stoi(pair.second.get_id()));
				_listen_sockets.push_back(sock);

				// std::cout << "heheheheheh: " << stoi(pair.second.get_id()) << std::endl;
				port_pair.first = stoi(pair.second.get_id());
				port_pair.second = 0;
				port_count.insert(port_pair);
				pair.first = pair.second.get_id() + "_0";
			}
			else
			{
				(*port_count.find(stoi(pair.second.get_id()))).second += 1;
				pair.first = pair.second.get_id() + "_" + std::to_string((*port_count.find(stoi(pair.second.get_id()))).second);
			}
			servers.insert(pair);
		}
		if (s.length() > m_c.next_start)
			s = s.substr(m_c.next_start);
		else
			break;
	}
}

void webserv::run(int test)
{
	std::cout << "~*~ Server running ~*~" << std::endl;
	std::cout << "Listening on ports (server name) : " << std::endl;

	for (std::map<std::string, server>::const_iterator i = servers.begin(); i != servers.end(); i++)
	{
		std::cout << (*i).first << " (" << (*i).second.get_server_name() << ")" << std::endl;
	}

	handle_client_connection();
}

void webserv::close_sockets(void)
{
	for (std::vector<listen_socket>::iterator it = _listen_sockets.begin(); it != _listen_sockets.end(); it++)
	{
		// std::cout << "closing _sockfd : " << it->get_fd() << std::endl;
		close(it->get_fd());
	}
	servers.clear();
}

// void webserv::run(void)
// {
// 	std::cout << "Server running : listening on port 8080 (test)" << std::endl;

// 	// Trouver les ports dans les serveurs :
// 	// server &server_one = this->servers.find("id_server")->second;
// 	// std::string const &port_one = server_one.get_id();
// 	// int port_int = atoi(port_one.c_str());

// 	// Pour l'instant on écoute sur le port 8080 de maniere arbitraire :
// 	int port = 8080;
// 	int backlog = 10; // maximum length to which the queue of pending connections for sockfd may grow.

// 	// Une struct sockaddr permet d'indiquer :
// 	// - AF_NET : on va utiliser des IPv4
// 	// - INADDR_ANY : on va travailler avec tous les IP dispo
// 	// - htons(port) : "host to network, short" traduit notre num de port en un nombre avec l'ordre de byte du network == compatibilité quelque soit les machine emetrice/receptrice avec lesquelles on bossera

// 	// on initialisera une struct sockaddr / port
// 	sockaddr_in sockaddr;
// 	bzero(&sockaddr, sizeof(sockaddr));
// 	sockaddr.sin_family = AF_INET;
// 	sockaddr.sin_addr.s_addr = INADDR_ANY;
// 	sockaddr.sin_port = htons(port); // htons is necessary to convert a number to
// 									 // network byte order

// 	// on initialise le(s) serveurs avec les données trouvées dans le fichier de config
// 	int server_fd = setup_server(port, backlog, sockaddr); // pour un seul serveur pour l'instant
// 	if (server_fd < 0)
// 	{
// 		throw(ServerInitFailed());
// 	}

// 	// on gere les connections clients
// 	handle_client_connection(server_fd, sockaddr);

// 	close(server_fd);
// }
