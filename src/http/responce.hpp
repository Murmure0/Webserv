
#ifndef RESPONCE_H
#define RESPONCE_H

#include "../../includes/webserv.hpp"

class responce
{
public:
	responce(void);
	responce(std::string header, std::string body, std::string addr, size_t content_size, std::map<std::string, std::string> *mime, t_responce_config config);
	~responce(void);
	responce(responce const &copy);
	responce &operator=(responce const &rhs);

	/*
	this function will check if method is allowed on ressource and dispatch between different methode of responce
	possible responce:
	- delete type
	- post type
	- get type
	- error page
	- index page
	*/
	std::string geterate_responce();

	/*
	generate an auto index page by listing directories and files in a location
	*/
	std::string generate_auto_index(std::string path, std::string url);

	/*
	generate a standard get responce if ressource exist. If not return a 404 error page.
	*/
	std::string generate_get_responce(std::string path, std::string http_version, std::string status, std::string mime, bool not_fail = false) ;

	void set_responce(std::string responce);

	std::string cuted_responce(void);

	bool is_sent(void) const;

	std::string get_response() { return _responce; }
	
	void set_error(std::string error) { _error = error; }

private:
	std::map<std::string, std::string> *_mime;
	t_responce_config _config;
	std::string _current_mime;
	std::string _method;
	std::string _responce;
	bool _responce_ready;
	bool _sent;
	std::string _body;
	std::map<std::string, std::string> _header;
	std::string _addr_ip;
	std::string _error;

	std::string cgi_execute();
	std::vector<std::string> cgi_env();
	std::map<std::string, std::string> header_to_map(std::string str);
	void child_process(int *fd_in, int *fd_out, char **env);
	std::string parent_process(pid_t pid, int *fd_out, int status);
	char **vec_to_char(std::vector<std::string> vec_env);
	std::string find_the_shebang_line();
	std::string	find_the_shebang_line(std::string script);
	bool file_existe();

	/// essais
	size_t _contentlenght;
};

#endif // RESPONCE_H
