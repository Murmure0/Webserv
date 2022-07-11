

#include "server.hpp"

server::server( void ) {
	std::cout << "server is born" << std::endl;
}

server::~server( void ) {
	std::cout << "server is gone" << std::endl;
}

server::server( server const &to_copy ) {}

server	&server::operator=( server const & rhs ) {
	return *this;
}

// size_t							_port;
// 		std::string						_server_names;
// 		std::string						_method;
// 		std::string						_root;
// 		std::string						_index;
// 		size_t							_max_body_size;
// 		bool							_autoindex;

void 	server::set(std::string key, std::string value) {
	if (key == "root")
		_root = value;
	else if (key == "index")
		_index = value;
	else if (key == "method")
		_method = value;
	else if (key == "server_name")
		_server_name = value;
}

void 	server::set(std::string key, size_t value) {
	if (key == "max_body_size")
		_max_body_size = value;
	else if (key == "listen")
		_port = value;
}

void 	server::set(std::string key, bool value) {
	if (key == "autoindex")
		_autoindex = value;
}