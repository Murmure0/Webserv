#include "../../includes/webserv.hpp"

#ifndef REQUEST_H
#define REQUEST_H

class request
{
public:
	request(void);
	~request(void);
	request(std::string addr);
	request(request const &copy);
	request &operator=(request const &rhs);

	void config_content_size(std::string header);

	/*
	this function will fill the request object by reading BUFFER_SIZE by BUFFER_SIZE char on specific fd
	*/
	int read_and_append(int fd);

	/*
	know if request is completed. Use to know when we need to create responce
	*/
	bool is_completed(void) const;
	std::string get_header(void) const;
	std::string get_body(void) const;
	std::string get_addr_ip(void) const;
	void set_request_config(void);
	std::string check_request_config(void) const;
	void clear(void);
	/*
	get string between host: and the next space
	this string look like: localhost:4040
	*/
	std::string get_port_location(void) const;

	/*
	get asked ressources
	*/
	std::string get_path(void) const;

	size_t get_content_size(void) const;

private:
	std::string _header, _body;
	std::string _addr_ip;
	size_t _content_size;
	bool _header_completed;
	bool _request_completed;
	request_config _request_config;
	std::string	_error;
};

#endif // REQUEST_H
