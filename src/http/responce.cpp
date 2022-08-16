

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
		ext = ext.substr(ext.find(".") + 1);
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

responce::responce(responce const &to_copy) : _mime(to_copy._mime), _config(to_copy._config), _current_mime(to_copy._current_mime), _method(to_copy._method), _sent(to_copy._sent) {}

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
	return *this;
}

std::string responce::geterate_responce()
{
	std::string cgi;

	if (_responce_ready)
		return _responce;
	if (_config.method.find(_method) == std::string::npos)
	{
		return generate_get_responce("./default_error_pages/405.html", "HTTP/1.1", "405 Method Not Allowed", "text/html", true);
	}

	// if delete method just delete the file. If not exist or not possible to delete return 404.
	if (_method == "DELETE")
	{
		int status;
		status = remove(_config.path.c_str());
		if (status == 0)
			return "HTTP/1.1 200 OK\r\n\r\n\r\n";
		else
			return "HTTP/1.1 404 Not Found\r\n\r\n\r\n";
	}

	if (_method == "POST")
	{
		cgi = cgi_execute();
		std::cout << "CGI == " << cgi << std::endl;
		if (cgi.empty())
			return generate_get_responce("./default_error_pages/500.html", "HTTP/1.1", "500 Internal Server Error", "text/html", true);
		return "HTTP/1.1 200 OK\nContent-Length: " + ft_to_string(cgi.size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + cgi + "\r\n";
		//voir quand utilisé le code status 201 Created, qd on a cree un fichier avec POST
	}

	// check if ask for auto index or return statdard get responce
	if (_current_mime.size() == 0)
	{
		if (!_config.autoindex)
			return generate_get_responce("./default_error_pages/404.html", "HTTP/1.1", "404 Not Found", "text/html", true);
		return generate_auto_index(_config.path, _config.url);
	}
	if (_config.path.find("?") != std::string::npos || _config.path.find(".py") != std::string::npos)
	{
		cgi = cgi_execute();
		if (cgi.empty())
			return generate_get_responce("./default_error_pages/500.html", "HTTP/1.1", "500 Internal Server Error", "text/html", true);
		return "HTTP/1.1 200 OK\nContent-Length: " + ft_to_string(cgi.size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + cgi + "\r\n";
	}
	return generate_get_responce(_config.path, "HTTP/1.1", "200 OK", _current_mime);
};

std::string responce::generate_auto_index(std::string path, std::string url) const
{
	std::string ret_str = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><title> Index of" + path + "</title></head><body>";
	DIR *cd;
	struct dirent *ci;

	ret_str += "<h1>Index of " + path + "</h1>";
	cd = opendir(path.c_str());
	// check if location is ok
	if (!cd)
		return generate_get_responce("./default_error_pages/404.html", "HTTP/1.1", "404 Not Found", "text/html", true);

	ci = readdir(cd);
	// loop in files and directories. the second arg url is used to create a complete path to the ressource
	while (ci)
	{
		ret_str += "<a href='" + (url == "/" ? "/" : url + "/") + std::string(ci->d_name) + "'>" + std::string(ci->d_name) + "</a></br>";
		ci = readdir(cd);
	}

	ret_str += "</body></html>";

	return "HTTP/1.1 200 OK\r\n\r\n" + ret_str + "\r\n";
}

std::string responce::generate_get_responce(std::string path, std::string http_version, std::string status, std::string mime, bool not_fail) const
{
	(void)mime;
	std::ifstream infile(path.c_str());

	if (!not_fail && !infile.good())
	{
		return generate_get_responce("./default_error_pages/404.html", "HTTP/1.1", "404 Not Found", "text/html", true);
	}

	std::stringstream ss;
	std::string str_resp;

	ss << infile.rdbuf();

	// adding the minimal http header-ever to the file content:
	str_resp = http_version + " " + status + "\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + ss.str() + "\r\n";
	// std::cout << ss.str().size() << std::endl;

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
