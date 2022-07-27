
#ifndef REQUEST_H
#define REQUEST_H

#include "../../includes/webserv.hpp"

class request
{
public:
	request(void);
	~request(void);
	request(request const &copy);
	request &operator=(request const &rhs);

	void config_content_size(std::string header);
	
	/*
	this function will fill the request object by reading BUFFER_SIZE by BUFFER_SIZE char on specific fd
	*/
	void read_and_append(int fd);
	bool is_completed(void) const;
	std::string get_header(void) const;
	std::string get_body(void) const;

	/*
	get string between host: and the next space
	this string look like: localhost:4040
	*/
	std::string get_port_location(void) const;

	/*
	get asked ressources
	*/
	std::string get_path(void) const;

private:
	std::string _header, _body;
	size_t _content_size;
	bool _header_completed;
	bool _request_completed;
};

#endif // REQUEST_H
