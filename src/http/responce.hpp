
#ifndef RESPONCE_H
#define RESPONCE_H

#include <string>
#include <iostream>
#include "../../includes/webserv.hpp"

class responce
{
public:
	responce(void);
	responce(std::string header, std::string body, std::map<std::string, std::string> *mime, t_responce_config config)
	{
		_config = config;
		_mime = mime;
	};
	~responce(void);
	responce(responce const &copy);
	responce &operator=(responce const &rhs);

	std::string geterate_responce(void)
	{
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
		else
		{
			_current_mime = std::string("text/html");
		}
		return generate_get_responce();
	};

	std::string generate_get_responce(void) const
	{
		std::ifstream infile(_config.path.c_str());

		if (!infile.good())
		{
			return generate_404();
		}

		std::stringstream ss;
		std::string str_resp;

		std::cout << _config.path << " " << _current_mime << std::endl;

		ss << infile.rdbuf();

		// adding the minimal http header-ever to the file content:
		str_resp = "HTTP/1.1 200 OK\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: " + _current_mime + "\r\n\r\n" + ss.str() + "\r\n";
		infile.close();
		return str_resp;
	}

	std::string generate_404(void) const
	{
		std::ifstream infile("./default_error_pages/404.html");
		std::stringstream ss;
		std::string str_resp;

		std::cout << _config.path << std::endl;

		ss << infile.rdbuf();

		// adding the minimal http header-ever to the file content:
		str_resp = "HTTP/1.1 404 Not Found\nContent-Length: " + ft_to_string(ss.str().size()) + "\nContent-Type: text/html" + "\r\n\r\n" + ss.str() + "\r\n";
		infile.close();
		return str_resp;
	}

private:
	std::map<std::string, std::string> *_mime;
	t_responce_config _config;
	std::string _current_mime;
};

#endif // RESPONCE_H
