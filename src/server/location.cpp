

#include "location.hpp"

location::location( void ) {
	std::cout << "location is born" << std::endl;
}

location::~location( void ) {
	std::cout << "location is gone" << std::endl;
}

location::location( location const &to_copy ) {}

location	&location::operator=( location const & rhs ) {
	return *this;
}
	