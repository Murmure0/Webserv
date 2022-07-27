

#ifndef LOCATION_H
#define LOCATION_H

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
	std::string get_location_match(void);

	/*
	used to overide server config
	*/
	void config_responce(t_responce_config *config);
	bool have_root(void);

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
