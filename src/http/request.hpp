
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

	void read_and_append(int fd)
	{
		char buffer[BUFFER_SIZE];
		size_t bytes_read;

		if (_request_completed)
			return;
		bytes_read = recv(fd, buffer, BUFFER_SIZE - 1, 0);
		if (!_header_completed)
		{
			_header += std::string(buffer, bytes_read);
			if (_header.find("\r\n\r\n") != std::string::npos)
			{
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
		std::cout << _body.size() << std::endl;
		if (_body.size() == _content_size)
		{
			_request_completed = true;
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

private:
	std::string _header, _body;
	size_t _content_size;
	bool _header_completed;
	bool _request_completed;
};

#endif // REQUEST_H
