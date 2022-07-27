

#include "responce.hpp"

responce::responce(void)
{
}

responce::~responce(void)
{
}

responce::responce(std::string header, std::string body, std::map<std::string, std::string> *mime, t_responce_config config)
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
};

responce::responce(responce const &to_copy) : _mime(to_copy._mime), _config(to_copy._config), _current_mime(to_copy._current_mime), _method(to_copy._method) {}

responce &responce::operator=(responce const &rhs)
{
	this->_mime = rhs._mime;
	this->_config = rhs._config;
	this->_current_mime = rhs._current_mime;
	this->_method = rhs._method;
	this->_header = rhs._header;
	return *this;
}


std::string responce::geterate_responce()
{
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
		// post method
	}

	// check if ask for auto index or return statdard get responce
	if (_current_mime.size() == 0)
	{
		if (!_config.autoindex)
			return generate_get_responce("./default_error_pages/404.html", "HTTP/1.1", "404 Not Found", "text/html", true);
		return generate_auto_index(_config.path, _config.url);
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
	std::ifstream infile(path.c_str());

	if (!not_fail && !infile.good())
	{
		return generate_get_responce("./default_error_pages/404.html", "HTTP/1.1", "404 Not Found", "text/html", true);
	}

	std::stringstream ss;
	std::string str_resp;
	std::string str_tmp;
	const char * str_tmp2;


	ss << infile.rdbuf();
	str_tmp = ss.str();

	// adding the minimal http header-ever to the file content:
	// str_resp = http_version + " " + status + "\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + ss.str() + "\r\n";
	str_resp = http_version + " " + status + "\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + (char *)str_tmp.str();
	std::cout << ss.str().size() << std::endl;

	infile.close();
	return str_resp;
}
