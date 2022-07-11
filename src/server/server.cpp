

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
	