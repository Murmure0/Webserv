

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include "../../includes/webserv.hpp"

class location
{
public:
	location(void);
	~location(void);
	location(location const &copy);
	location &operator=(location const &rhs);

	void print(void) const;

	void set(std::string key, std::string value);

	std::string get_location_match(void)
	{
		return _location_match;
	}

	/*
	used to overide server config
	*/
	void config_responce(t_responce_config *config)
	{
		if (_autoindex_set)
		{
			(*config).autoindex = _autoindex;
		}
		if (_max_body_size != 0)
			(*config).max_body_size = _max_body_size;
		if (_method.size() != 0)
			(*config).method = _method;
		if (_root.size() != 0)
			(*config).path = _root;
		if (_index.size() != 0)
			(*config).index = _index;
		if (_root.size() != 0)
			(*config).root = _root;
	}

	bool have_root(void)
	{
		return !_root.empty();
	}

private:
	std::string _location_match;
	std::string _method;
	std::string _root;
	std::string _index;
	std::string _uploads;
	std::string _directory_listing;
	size_t _max_body_size;
	bool _autoindex;
	bool _autoindex_set;
};

#endif // LOCATION_H
