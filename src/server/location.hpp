

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
	void set(std::string key, size_t value);
	void set(std::string key, bool value);

private:
	std::string _location_match;
	std::string _method;
	std::string _root;
	std::string _index;
	std::string _uploads;
	std::string _directory_listing;
	size_t _max_body_size;
	bool _autoindex;
};

#endif // LOCATION_H
