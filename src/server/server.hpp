

#ifndef SERVER_H
#define SERVER_H

#include "location.hpp"
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

	/*
	this function will return the longest location match inside of the server config with the given path
	*/
	location *get_location(std::string path);
	void config_responce(t_responce_config *config);

	std::map<std::string, std::string> &get_error_pages(void);

private:
	size_t _port;
	std::string _server_name;
	std::string _method;
	std::string _root;
	std::string _index;
	std::map<std::string, std::string> _error_pages;
	size_t _max_body_size;
	bool _autoindex;

	std::map<std::string, location> _locations;
};

#endif // SERVER_H
