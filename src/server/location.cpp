

#include "location.hpp"

location::location(void)
{
	this->_autoindex = false;
	this->_autoindex_set = false;
	this->_max_body_size = -1;
}

location::~location(void)
{
}

location::location(location const &copy)
{
	this->_autoindex = copy._autoindex;
	this->_index = copy._index;
	this->_directory_listing = copy._directory_listing;
	this->_max_body_size = copy._max_body_size;
	this->_method = copy._method;
	this->_location_match = copy._location_match;
	this->_root = copy._root;
	this->_uploads = copy._uploads;
	this->_autoindex_set = copy._autoindex_set;
	this->_error_pages = copy._error_pages;
}

location &location::operator=(location const &rhs)
{
	this->_autoindex = rhs._autoindex;
	this->_index = rhs._index;
	this->_directory_listing = rhs._directory_listing;
	this->_max_body_size = rhs._max_body_size;
	this->_method = rhs._method;
	this->_location_match = rhs._location_match;
	this->_root = rhs._root;
	this->_uploads = rhs._uploads;
	this->_autoindex_set = rhs._autoindex_set;
	this->_error_pages = rhs._error_pages;
	return *this;
}

// a enlever
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
	{
		if (value.empty())
			_autoindex = true;
		else
			_autoindex = (value == "on") ? true : false;
		_autoindex_set = true;
	}
	else if (key == "error_page")
	{
		_error_pages[value.substr(0, value.find(" "))] = value.substr(value.find(" ") + 1);
	}
}

std::string location::get_location_match(void)
{
	return _location_match;
}

void location::config_responce(t_responce_config *config)
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

bool location::have_root(void)
{
	return !_root.empty();
}

std::map<std::string, std::string> &location::get_error_pages(void)
{
	return _error_pages;
}