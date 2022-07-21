

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "location.hpp"
#include <utility>
#include "../../includes/webserv.hpp"

class server
{
public:
	server(void);
	~server(void);
	server(server const &copy);
	server &operator=(server const &rhs);

	void print(void) const;

	void set(std::string key, std::string value);
	void set(std::string key, size_t value);
	void set(std::string key, bool value);

	std::string get_id(void) const;
	std::string get_server_name(void) const;
	void add_location(std::pair<std::string, location> l_pair);

	location *get_location(std::string path)
	{
		std::string max_loc;

		for (std::map<std::string, location>::iterator i = _locations.begin(); i != _locations.end(); i++)
		{
			if (path.find((*i).first) != std::string::npos && (*i).first.size() > max_loc.size())
			{
				max_loc = (*i).first;
			}
		}
		if (max_loc.size() == 0)
			return NULL;
		return &_locations[max_loc];
	}

	void config_responce(t_responce_config *config)
	{
		(*config).autoindex = _autoindex;
		(*config).max_body_size = _max_body_size;
		(*config).method = _method;
		(*config).path = _root;
	}

private:
	size_t _port;
	std::string _server_name;
	std::string _method;
	std::string _root;
	std::string _index;
	size_t _max_body_size;
	bool _autoindex;

	std::map<std::string, location> _locations;
};

#endif // SERVER_H
