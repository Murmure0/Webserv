
#include "request.hpp"

request::request(void) : _content_size(-1), _header_completed(false), _request_completed(false)
{
}

request::request(std::string addr) : _content_size(-1), _header_completed(false), _request_completed(false)
{
	_addr_ip = addr;
}

request::~request(void)
{
}

request::request(request const &to_copy) : _content_size(to_copy._content_size), _header_completed(to_copy._header_completed), _request_completed(to_copy._request_completed) {}

request &request::operator=(request const &rhs)
{
	this->_addr_ip = rhs._addr_ip;
	return *this;
}

void request::config_content_size(std::string header)
{
	size_t content_size_pos = header.find("Content-Length");
	if (content_size_pos != std::string::npos)
	{
		std::string sub = header.substr(content_size_pos + 16);
		this->_content_size = atoi(sub.substr(0, sub.find("\n")).c_str());
	}
	else
	{
		this->_content_size = 0;
	}
};

void request::read_and_append(int fd)
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

bool request::is_completed(void) const
{
	return _request_completed;
}

std::string request::get_header(void) const
{
	return _header;
}

std::string request::get_body(void) const
{
	return _body;
}

std::string request::get_port_location(void) const
{
	std::string host = _header.substr(_header.find("Host: ") + 6);
	host = host.substr(0, host.find('\n') - 1);
	return host;
}

std::string request::get_path(void) const
{
	std::string path = _header.substr(0, _header.find("\n") - 1);
	path = path.substr(path.find(" ") + 1);
	path = path.substr(0, path.find(" "));
	return path;
}

size_t		request::get_content_size(void) const
{
	return this->_content_size;
}

std::string	request::get_addr_ip(void) const
{
	return this->_addr_ip;
}
