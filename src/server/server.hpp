

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "location.hpp"
#include <utility>

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
