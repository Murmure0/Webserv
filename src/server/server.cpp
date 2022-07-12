

#include "server.hpp"

server::server(void)
{
}

server::~server(void)
{
}

server::server(server const &to_copy)
{
	this->_index = to_copy._index;
}

server &server::operator=(server const &rhs)
{
	return *this;
}

void server::print(void) const
{
	std::cout << "Server " << get_id() << std::endl;
	std::cout << "_autoindex " << this->_autoindex << std::endl;
	std::cout << "_index " << this->_index << std::endl;
	std::cout << "_locations " << this->_locations.size() << std::endl;
	std::cout << "_max_body_size " << this->_max_body_size << std::endl;
	std::cout << "_method " << this->_method << std::endl;
	std::cout << "_port " << this->_port << std::endl;
	std::cout << "_root " << this->_root << std::endl;
	std::cout << "_server_name " << this->_server_name << std::endl;
};

void server::set(std::string key, std::string value)
{
	if (key == std::string("root"))
		_root = value;
	else if (key == std::string("index"))
		_index = value;
	else if (key == std::string("method"))
		_method = value;
	else if (key == std::string("server_name"))
		_server_name = value;
}

void server::set(std::string key, size_t value)
{
	if (key == "max_body_size")
		_max_body_size = value;
	else if (key == "listen")
		_port = value;
}

void server::set(std::string key, bool value)
{
	if (key == "autoindex")
		_autoindex = value;
}

std::string server::get_id(void) const
{
	return std::to_string(_port);
}