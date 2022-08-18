

#include "responce.hpp"

responce::responce(void)
{
}

responce::~responce(void)
{
}

responce::responce(std::string header, std::string body, std::string addr, size_t content_size, std::map<std::string, std::string> *mime, t_responce_config config) : _responce_ready(false), _sent(false)
{
	_config = config;
	_mime = mime;
	std::string ext;
	ext = _config.path.substr(_config.path.find_last_of("/"));
	if (ext.find(".") != std::string::npos)
	{
		ext = ext.substr(ext.find_last_of(".") + 1);
		if (ext.size() && _mime->find(ext) != _mime->end())
			_current_mime = (*_mime->find(ext)).second;
		else
			_current_mime = std::string("text/html");
	}
	_method = header.substr(0, header.find(" "));
	_header = header_to_map(header);
	_contentlenght = content_size;
	_body = body;
	_addr_ip = addr;
};

responce::responce(responce const &to_copy) : _mime(to_copy._mime), _config(to_copy._config), _current_mime(to_copy._current_mime), _method(to_copy._method), _sent(to_copy._sent), _error(to_copy._error) {}

responce &responce::operator=(responce const &rhs)
{
	this->_mime = rhs._mime;
	this->_config = rhs._config;
	this->_current_mime = rhs._current_mime;
	this->_method = rhs._method;
	this->_header = rhs._header;
	this->_responce_ready = rhs._responce_ready;
	this->_responce = rhs._responce;
	this->_sent = rhs._sent;
	this->_contentlenght = rhs._contentlenght;
	this->_body = rhs._body;
	this->_addr_ip = rhs._addr_ip;
	this->_error = rhs._error;
	return *this;
}

std::string responce::geterate_responce()
{
	std::string cgi;
	std::string all_methods = "GET|POST|DELETE";

	if (_responce_ready)
		return _responce;
	if (!_error.empty()) {
		return generate_get_responce(_config.error_pages[_error.substr(0, 3)], "HTTP/1.1", _error, "text/html", true);
	}
	if (!_config.redirect.empty())
	{
		std::string code = _config.redirect.substr(0, _config.redirect.find(" "));
		std::string url = _config.redirect.substr(_config.redirect.find(" ") + 1);
		if (code == "308")
			return "HTTP/1.1 " + code + " Permanent Redirect" + "\n" + "Location: " + url + "\n\r\n\r\n\r";
		return "HTTP/1.1 " + code + " Moved Permanently" + "\n" + "Location: " + url + "\n\r\n\r\n\r";
	}

	if (_config.max_body_size < _body.length() && _config.max_body_size != 0) {
		return generate_get_responce(_config.error_pages["413"], "HTTP/1.1", "413 Request Entity Too Large", "text/html", true);
	}

	if (all_methods.find(_method) == std::string::npos || _method.find_first_of("|") != std::string::npos)
	{
		return generate_get_responce(_config.error_pages["501"], "HTTP/1.1", "501 Not Implemented Error", "text/html", true);
	}

	if (_config.method.find(_method) == std::string::npos)
	{
		return generate_get_responce(_config.error_pages["405"], "HTTP/1.1", "405 Method Not Allowed", "text/html", true);
	}

	// if delete method just delete the file. If not exist or not possible to delete return 404.
	if (_method == "DELETE")
	{
		int status;
		status = remove(_config.path.c_str());
		if (status == 0)
			return "HTTP/1.1 204 No Content\nContent-Length: 0\r\n\r\n\r\n";
		else
			return generate_get_responce(_config.error_pages["404"], "HTTP/1.1", "404 Not Found", "text/html", true);
	}

	if (_method == "POST")
	{
		cgi = cgi_execute();
		if (cgi.empty())
			return generate_get_responce(_config.error_pages["500"], "HTTP/1.1", "500 Internal Server Error", "text/html", true);
		if (cgi == "404")
			return generate_get_responce(_config.error_pages["404"], "HTTP/1.1", "404 Not Found", "text/html", true);
		return "HTTP/1.1 201 Created\nContent-Length: " + ft_to_string(cgi.size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + cgi + "\r\n";
	}

	// check if ask for auto index or return statdard get responce
	if (_current_mime.size() == 0)
	{
		if (!_config.autoindex)
			return generate_get_responce(_config.error_pages["404"], "HTTP/1.1", "404 Not Found", "text/html", true);
		return generate_auto_index(_config.path, _config.url);
	}
	if (_config.path.find(".pl") != std::string::npos || _config.path.find(".py") != std::string::npos || _config.path.find(".php") != std::string::npos)
	{
		cgi = cgi_execute();
		if (cgi.empty())
			return generate_get_responce(_config.error_pages["500"], "HTTP/1.1", "500 Internal Server Error", "text/html", true);
		if (cgi == "404")
			return generate_get_responce(_config.error_pages["404"], "HTTP/1.1", "404 Not Found", "text/html", true);
		return "HTTP/1.1 200 OK\nContent-Length: " + ft_to_string(cgi.size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + cgi + "\r\n";
	}
	_config.path = _config.path.substr(0, _config.path.find("?"));
	return generate_get_responce(_config.path, "HTTP/1.1", "200 OK", _current_mime);
};

std::string responce::generate_auto_index(std::string path, std::string url)
{
	std::string ret_str = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><title> Index of" + path + "</title></head><body>";
	DIR *cd;
	struct dirent *ci;

	ret_str += "<h1>Index of " + path + "</h1>";
	cd = opendir(path.c_str());
	// check if location is ok
	if (!cd)
		return generate_get_responce(_config.error_pages["404"], "HTTP/1.1", "404 Not Found", "text/html", true);

	ci = readdir(cd);
	// loop in files and directories. the second arg url is used to create a complete path to the ressource
	while (ci)
	{
		ret_str += "<a href='" + (url == "/" ? "/" : url + "/") + std::string(ci->d_name) + "'>" + std::string(ci->d_name) + "</a></br>";
		ci = readdir(cd);
	}

	ret_str += "</body></html>";

	return "HTTP/1.1 200 OK\nContent-Length: " + ft_to_string(ret_str.length()) + "\nContent-Type: text/html\r\n\r\n" + ret_str + "\r\n";
}

std::string responce::generate_get_responce(std::string path, std::string http_version, std::string status, std::string mime, bool not_fail)
{
	(void)mime;
	std::ifstream infile(path.c_str());

	if (!not_fail && !infile.good())
	{
		return generate_get_responce(_config.error_pages["404"], "HTTP/1.1", "404 Not Found", "text/html", true);
	}

	std::stringstream ss;
	std::string str_resp;

	ss << infile.rdbuf();

	// adding the minimal http header-ever to the file content:
	str_resp = http_version + " " + status + "\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + ss.str() + "\r\n";

	infile.close();
	return str_resp;
}

void responce::set_responce(std::string responce)
{
	if (!_responce_ready)
	{
		_responce = responce;
		_responce_ready = true;
	}
}

std::string responce::cuted_responce(void)
{
	std::string cuted = _responce.substr(0, SEND_BUFFER_SIZE - 1);

	if (_responce.size() < SEND_BUFFER_SIZE)
		_responce = "";
	else
		_responce = _responce.substr(SEND_BUFFER_SIZE - 1);
	if (_responce.size() == 0)
		_sent = true;
	return cuted;
}

bool responce::is_sent(void) const
{
	return _sent;
}
