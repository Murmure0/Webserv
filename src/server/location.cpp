

#include "location.hpp"

location::location(void)
{
	this->_autoindex = false;
	this->_max_body_size = -1;
}

location::~location(void)
{
}

void location::print(void) const
{
	std::cout << "\t"
			  << "--- Location " << this->_location_match << " ---" << std::endl;
	std::cout << "\t"
			  << "_autoindex " << this->_autoindex << std::endl;
	std::cout << "\t"
			  << "_index " << this->_index << std::endl;
	std::cout << "\t"
			  << "_max_body_size " << this->_max_body_size << std::endl;
	std::cout << "\t"
			  << "_method " << this->_method << std::endl;
	std::cout << "\t"
			  << "_directory_listing " << this->_directory_listing << std::endl;
	std::cout << "\t"
			  << "_root " << this->_root << std::endl;
	std::cout << "\t"
			  << "_uploads " << this->_uploads << std::endl
			  << std::endl;
};

location::location(location const &to_copy)
{
	this->_autoindex = to_copy._autoindex;
	this->_index = to_copy._index;
	this->_directory_listing = to_copy._directory_listing;
	this->_max_body_size = to_copy._max_body_size;
	this->_method = to_copy._method;
	this->_location_match = to_copy._location_match;
	this->_root = to_copy._root;
	this->_uploads = to_copy._uploads;
}

location &location::operator=(location const &rhs)
{
	return *this;
}

void location::set(std::string key, std::string value)
{
	if (key == "root")
		_root = value;
	else if (key == "location_match")
		_location_match = value;
	else if (key == "index")
		_index = value;
	else if (key == "method")
		_method = value;
	else if (key == "uploads")
		_uploads = value;
	else if (key == "directory_listing")
		_directory_listing = value;
	else if (key == "max_body_size")
		_max_body_size = atol(value.c_str());
	else if (key == "autoindex")
		_autoindex = value == std::string("true") ? true : false;
}
