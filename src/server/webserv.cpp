

#include "webserv.hpp"

webserv::webserv( void ) {
	std::cout << "webserv is born" << std::endl;
}

webserv::~webserv( void ) {
	std::cout << "webserv is gone" << std::endl;
}

webserv::webserv( webserv const &to_copy ) {}

webserv	&webserv::operator=( webserv const & rhs ) {
	return *this;
}

void webserv::config( std::string config_file ) {
	server s;
	servers.insert(std::make_pair("8080_localhost", s));
}