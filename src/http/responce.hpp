
#ifndef RESPONCE_H
#define RESPONCE_H

#include <string>
#include <iostream>

class responce
{
public:
	responce(void);
	responce(std::string header, std::string body)
	{
		if (header.substr(0, header.find("\n")).find(".jpeg") != std::string::npos)
		{
			is_image = true;
			std::cout << "Hey" << std::endl;
		}
	};
	~responce(void);
	responce(responce const &copy);
	responce &operator=(responce const &rhs);

	bool is_image = false;
};

#endif // RESPONCE_H
