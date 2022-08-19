

#include "../../includes/webserv.hpp"

void welcome(void) {
	std::ifstream infile("./src/utils/welcome.txt");
	std::stringstream ss;
	std::string str_resp;

	ss << infile.rdbuf();
	std::cout << std::endl << std::endl << std::endl;
	std::cout << KCYN << ss.str() << RST << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}

void bye(void) {
	std::cout << std::endl << std::endl << std::endl;
	std::ifstream infile("./src/utils/bye.txt");
	std::stringstream ss;
	std::string str_resp;

	ss << infile.rdbuf();
	std::cout << std::endl << std::endl << std::endl;
	std::cout << KCYN << ss.str() << RST << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}