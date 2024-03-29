

#include "server.hpp"

server::server(void)
{
	this->_autoindex = false;
	this->_max_body_size = -1;
	this->_port = -1;
}

server::~server(void)
{
}

server::server(server const &to_copy)
{
	this->_autoindex = to_copy._autoindex;
	this->_index = to_copy._index;
	this->_locations = to_copy._locations;
	this->_max_body_size = to_copy._max_body_size;
	this->_method = to_copy._method;
	this->_port = to_copy._port;
	this->_root = to_copy._root;
	this->_server_name = to_copy._server_name;
	this->_error_pages = to_copy._error_pages;
	this->_redirect = to_copy._redirect;
}

server &server::operator=(server const &rhs)
{
	this->_autoindex = rhs._autoindex;
	this->_index = rhs._index;
	this->_locations = rhs._locations;
	this->_max_body_size = rhs._max_body_size;
	this->_method = rhs._method;
	this->_port = rhs._port;
	this->_root = rhs._root;
	this->_server_name = rhs._server_name;
	this->_error_pages = rhs._error_pages;
	this->_redirect = rhs._redirect;
	return *this;
}

void server::print(void) const
{
	std::cout << "-------------------- Server " << get_id() << " ( " << (_server_name.empty() ? "" : _server_name) << " ) --------------------" << std::endl;
	std::cout << "_autoindex " << this->_autoindex << std::endl;
	std::cout << "_index " << this->_index << std::endl;
	std::cout << "_max_body_size " << this->_max_body_size << std::endl;
	std::cout << "_method " << this->_method << std::endl;
	std::cout << "_port " << this->_port << std::endl;
	std::cout << "_root " << this->_root << std::endl;
	std::cout << "_server_name " << this->_server_name << std::endl
			  << std::endl;
	for (std::map<std::string, location>::const_iterator i = _locations.begin(); i != _locations.end(); i++)
	{
		(*i).second.print();
	}
};

void server::set(std::string key, std::string value)
{
	if (key == "root")
		_root = value;
	else if (key == "index")
		_index = value;
	else if (key == "method")
		_method = value;
	else if (key == "server_name")
		_server_name = value;
	else if (key == "max_body_size")
	{
		_max_body_size = atol(value.c_str());
	}
	else if (key == "listen")
		_port = atoi(value.c_str());
	else if (key == "autoindex")
	{
		if (value.empty())
			_autoindex = true;
		else
			_autoindex = (value == "on") ? true : false;
	}
	else if (key == "error_page")
	{
		_error_pages[value.substr(0, value.find(" "))] = value.substr(value.find(" ") + 1);
	}
	else if (key == "return")
		_redirect = value;
}

std::string server::get_id(void) const
{
	return ft_to_string(_port);
}

std::string server::get_server_name(void) const
{
	return (_server_name);
}

void server::add_location(std::pair<std::string, location> l_pair)
{
	_locations.insert(l_pair);
}

location *server::get_location(std::string path)
{
	std::string max_loc;

	path += "/";
	for (std::map<std::string, location>::iterator i = _locations.begin(); i != _locations.end(); i++)
	{
		if (path.find((*i).first + "/") != std::string::npos && (*i).first.size() > max_loc.size())
		{
			max_loc = (*i).first;
		}
		else if ((*i).first == "/")
		{
			max_loc = (*i).first;
		}
	}
	if (max_loc.size() == 0)
		return NULL;
	return &_locations[max_loc];
}

void server::config_responce(t_responce_config *config)
{
	(*config).autoindex = _autoindex;
	(*config).max_body_size = _max_body_size;
	(*config).method = _method;
	(*config).path = _root;
	(*config).index = _index;
	(*config).root = _root;
	(*config).redirect = _redirect;
}

std::map<std::string, std::string> &server::get_error_pages(void)
{
	return _error_pages;
}