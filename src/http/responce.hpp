
#ifndef RESPONCE_H
#define RESPONCE_H

#include <string>
#include <iostream>
#include "../../includes/webserv.hpp"

class responce
{
public:
	responce(void);
	responce(std::string header, std::string body, std::map<std::string, std::string> *mime)
	{
		std::cout << (*mime)["pdf"] << std::endl;
	};
	~responce(void);
	responce(responce const &copy);
	responce &operator=(responce const &rhs);

	std::string geterate_responce(void) const
	{
		return "n";
	};

private:
	std::map<std::string, std::string> *_mime;
};

#endif // RESPONCE_H
