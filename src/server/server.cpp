

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
}

server &server::operator=(server const &rhs)
{
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
		_port = std::stoi(value);
	else if (key == "autoindex")
		_autoindex = value == std::string("true") ? true : false;
}

std::string server::get_id(void) const
{
	return std::to_string(_port);
}

void server::add_location(std::pair<std::string, location> l_pair)
{
	_locations.insert(l_pair);
}