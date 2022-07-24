
#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>
#include "../../includes/webserv.hpp"

class request
{
public:
	request(void);
	~request(void);
	request(request const &copy);
	request &operator=(request const &rhs);

	void config_content_size(std::string header)
	{
		size_t content_size_pos = header.find("Content-Length");
		if (content_size_pos != std::string::npos)
		{
			std::string sub = header.substr(content_size_pos + 16);
			_content_size = atoi(sub.substr(0, sub.find("\n")).c_str());
		}
		else
		{
			_content_size = 0;
		}
	};

	/*
	this function will fill the request object by reading BUFFER_SIZE by BUFFER_SIZE char on specific fd
	*/
	void read_and_append(int fd)
	{
		char buffer[BUFFER_SIZE];
		size_t bytes_read;

		if (_request_completed)
			return;
		bytes_read = recv(fd, buffer, BUFFER_SIZE - 1, 0);
		// if header is not fully received
		if (!_header_completed)
		{
			// append and check if end of header present
			_header += std::string(buffer, bytes_read);
			if (_header.find("\r\n\r\n") != std::string::npos)
			{
				// std::cout << _header.substr(0, _header.find("\n") - 1) << std::endl;
				// if end of header set header completed and add in body the part of body in the string we have (after /n/r/n/r)
				_header_completed = true;
				_body = _header.substr(_header.find("\r\n\r\n") + 4);
				_header = _header.substr(0, _header.find("\r\n\r\n"));
				config_content_size(_header);
			}
		}
		else
		{
			_body += std::string(buffer, bytes_read);
		}
		// std::cout << _body.size() << std::endl;
		if (_body.size() == _content_size)
		{
			_request_completed = true;
			// std::cout << _header << std::endl;
		}
	}

	bool is_completed(void) const
	{
		return _request_completed;
	}

	std::string get_header(void) const
	{
		return _header;
	}

	std::string get_body(void) const
	{
		return _body;
	}

	/*
	get string between host: and the next space
	this string look like: localhost:4040
	*/
	std::string get_port_location(void) const
	{
		std::string host = _header.substr(_header.find("Host: ") + 6);
		host = host.substr(0, host.find('\n') - 1);
		return host;
	}

	/*
	get asked ressources
	*/
	std::string get_path(void) const
	{
		std::string path = _header.substr(0, _header.find("\n") - 1);
		path = path.substr(path.find(" ") + 1);
		path = path.substr(0, path.find(" "));
		return path;
	}

private:
	std::string _header, _body;
	size_t _content_size;
	bool _header_completed;
	bool _request_completed;
};

#endif // REQUEST_H
