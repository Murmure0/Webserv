

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
	std::string s = file_to_string(config_file);

	t_config c;
	int i = 0;
	while ((++i < 10 && !c.key.empty()) || i == 1)
	{
		std::cout << "___________________" << std::endl;
		std::cout << s << std::endl;
		
		print_line(c);
		c = get_next_variable(s);
		std::cout << c.next_start << std::endl;
		if (s.length() > c.next_start)
			s = s.substr(c.next_start);
		else
			break;
	}
	
	
}
