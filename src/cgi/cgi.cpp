#include "../http/responce.hpp"
#include "sys/wait.h"

/*Fonction utile au CGI car elle permet lors de l'initialisation de la re2ponse, de transformer le header
de la requete qui est en std::string en map<std::string, std::string>*/
std::map<std::string, std::string>	responce::header_to_map(std::string str)
{
	std::map<std::string, std::string>	map_header;
	std::string	value;
	std::string	key;

	key = "Method:";
	value = str.substr(0, str.find(" "));
	str.erase(0, str.find('\n')+1);
	map_header.insert(std::make_pair(key,value));
	while (!str.empty())
	{
		key = str.substr(0, str.find(":")+1);
		value = str.substr(str.find(" ")+1, str.find('\r') - 1 -(str.find(":") + 1));
		if (str.find('\n') == std::string::npos)
		{
			value = str.substr(str.find(" ")+1, str.find('\r') - 1 -(str.find(":") + 1));
			str.clear();
		}
		str.erase(0, str.find('\n')+1);
		map_header.insert(std::make_pair(key, value));
	}
	return (map_header);
}

std::vector<std::string>	responce::cgi_env()
{
	std::vector<std::string>	env;
	std::string					tmp;
	char						tmp_path[PATH_MAX];

	env.push_back("AUTH_TYPE=");

	env.push_back("SERVER_SOFTWARE=WEBSERV/1.1");

	tmp = _header.find("Host:")->second;
	env.push_back("SERVER_NAME=" + tmp.substr(0, tmp.find(":")));

	env.push_back("GATEWAY_INTERFACE=CGI/1.1");

	env.push_back("SERVER_PROTOCOL=HTTP/1.1");

	env.push_back("SERVER_PORT=" + tmp.substr(tmp.find(":")+1));

	env.push_back("REQUEST_METHOD=" + _header.at("Method:"));

	///PATH_INFO:Extra path information passed to a CGI program.
	///TO DO voir si pas un probleme avec le testeur de l'école mais pour le moment ça suit la RFC
	if (_header.at("Method:") == "GET")
		env.push_back("PATH_INFO=" + _config.path.substr(_config.path.find("?") + 1));
	else
		env.push_back("PATH_INFO=");

	getcwd(tmp_path, PATH_MAX);
	env.push_back(std::string ("PATH_TRANSLATE=") + tmp_path + "/" + _config.path.substr(2));

	if (_header.at("Method:") == "GET")
		env.push_back("SCRIPT_NAME=" + _config.path.substr(0, _config.path.find("?")));
	else
		env.push_back("SCRIPT_NAME=" + _config.path.substr(0));

	if (_config.path.find("?") != std::string::npos)
		env.push_back("QUERY_STRING=" + _config.path.substr(_config.path.find("?") + 1));

	env.push_back("REMOTE_HOST=");

	if (_header.at("Method:") == "POST")
		env.push_back("CONTENT_TYPE=" + _header.at("Content-Type:"));

	if (_header.at("Method:") == "POST")
		env.push_back("CONTENT_LENGTH=" + ft_to_string(_contentlenght));
	else
		env.push_back("CONTENT_LENGTH=");

	if (_header.find("Accept:") != _header.end())
		env.push_back("HTTP_ACCEPT=" + _header.at("Accept:"));

	if (_header.find("Accept-Language:") != _header.end())
		env.push_back("HTTP_ACCEPT_LANGUAGE=" + _header.at("Accept-Language:"));

	if (_header.find("User-Agent:") != _header.end())
		env.push_back("HTTP_USER_AGENT=" + _header.at("User-Agent:"));

	if (_header.find("Referer:") != _header.end())
		env.push_back("HTTP_REFERER=" + _header.at("Referer:"));

	env.push_back("REMOTE_ADDR=" + _addr_ip);

	env.push_back("REMOTE_IDENT=");

	env.push_back("REMOTE_USER=");

	if (_header.find("Cookie:") != _header.end())
		env.push_back("HTTP_COOKIE=" + _header.at("Cookie:"));
	return env;
}

char		**responce::vec_to_char(std::vector<std::string> vec_env)
{
	char		**env = new char*[vec_env.size() + 1];
	size_t		it = 0;
	const char	*str;

	while (it < vec_env.size())
	{
		env[it] = new char[vec_env[it].size() + 1];
		str = vec_env[it].c_str();
		strcpy(env[it], str);
		it++;
	}
	env[it] = NULL;
	return env;
}

std::string	responce::find_the_shebang_line()
{
	std::map<std::string, std::string>	map;
	std::string							tmp;

	tmp = "cgi-bin" + _config.path.substr(_config.path.rfind("/"));
	if (tmp.find("?") != std::string::npos)
		tmp.erase(tmp.find("?"));
	tmp = tmp.substr(tmp.rfind("."));

	map.insert(std::make_pair(".py", "/usr/bin/python3"));
	map.insert(std::make_pair(".php", "/usr/bin/php"));
	map.insert(std::make_pair(".pl", "/usr/bin/perl"));
	if (map.find(tmp) == map.end())
		return "";
	return map.find(tmp)->second;
}

std::string	responce::find_the_shebang_line(std::string script)
{
	std::map<std::string, std::string>	map;
	std::string							tmp;

	tmp = script.substr(script.rfind("."));

	map.insert(std::make_pair(".py", "/usr/bin/python3"));
	map.insert(std::make_pair(".php", "/usr/bin/php"));
	map.insert(std::make_pair(".pl", "/usr/bin/perl"));

	return map.find(tmp)->second;
}

void	responce::child_process(int *fd_in, int *fd_out, char **env)
{
	if (dup2(fd_in[0], STDIN_FILENO) == -1)
		exit(1);
	if (dup2(fd_out[1], STDOUT_FILENO) == -1)
		exit(1);
	close(fd_in[0]);
	close(fd_in[1]);
	close(fd_out[0]);
	close(fd_out[1]);

	char *av[3];
	std::string	tmp = "cgi-bin" + _config.path.substr(_config.path.rfind("/"));
	if (tmp.find("?") != std::string::npos)
		tmp.erase(tmp.find("?"));
	///For The moment we manage the python/php/pearl langage
	std::string shebang_line = find_the_shebang_line(tmp);

	av[0] = (char *)shebang_line.c_str();
	av[1] = (char *)tmp.c_str();
	av[2] = NULL;

	execve(av[0], av, env);

	exit(1);
}

std::string	responce::parent_process(pid_t pid, int *fd_out, int status)
{
	char			tmp[BUFFER_SIZE + 1] = {0};
	std::string		str_return;
	int				ret = 1;

	waitpid(pid, &status, 0);
	while (ret > 0)
	{
		ret = read(fd_out[0], tmp, BUFFER_SIZE);
		tmp[ret] = '\0';
		str_return += std::string(tmp);
	}
	close(fd_out[0]);
	return str_return;
}

bool	responce::file_existe()
{
	std::string	path = _config.path.substr(_config.path.rfind('/'));

	if (path.find("?") != std::string::npos)
		path.erase(path.find("?"));
	if (path == "/" || path.find(".") == std::string::npos)
		return 0;
	std::ifstream	infile("cgi-bin" + path);
	if (infile.good())
		return 1;
	return 0;
}

std::string	responce::cgi_execute()
{
	char		**env;
	int			fd_in[2]; //body
	int			fd_out[2]; //family
	pid_t		pid;
	int			status = 0;

	(void)env;
	if (!file_existe() || (_body.empty() && _method == "POST"))
		return "404";
	if (find_the_shebang_line().empty())
		return "";
	env = vec_to_char(cgi_env());
	if (pipe(fd_in) == -1)
		return "";
	if(pipe(fd_out) == -1)
		return "";
	pid = fork();
	if (pid == -1)
		return "";
	else if (pid == 0)
		child_process(fd_in, fd_out, env);
	if (dup2(fd_in[0], 0) == -1)
		return "";
	if (_header.at("Method:") == "POST")
		write(fd_in[1], _body.c_str(), _body.size());
	close(fd_in[1]);
	close(fd_in[0]);
	close(fd_out[1]);

	return parent_process(pid, fd_out, status);
}
