

#include "location.hpp"

location::location(void)
{
}

location::~location(void)
{
}

location::location(location const &to_copy) {}

location &location::operator=(location const &rhs)
{
	return *this;
}

void location::set(std::string key, std::string value)
{
	if (key == "root")
		_root = value;
	else if (key == "index")
		_index = value;
	else if (key == "method")
		_method = value;
	else if (key == "uploads")
		_uploads = value;
	else if (key == "directory_listing")
		_directory_listing = value;
}

void location::set(std::string key, size_t value)
{
	if (key == "max_body_size")
		_max_body_size = value;
}

void location::set(std::string key, bool value)
{
	if (key == "autoindex")
		_autoindex = value;
}