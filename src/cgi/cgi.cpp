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
	std::cout << "config : " << _config.path << std::endl;
	std::vector<std::string>	env;
	std::string					tmp;
	char						tmp_path[PATH_MAX];
	/*-----------------------------------SERVER_INFORMATION-------------------------------------------------*/

	///AUTH_TYPE:The authentication method used to validate a user.
	///For HTTP, if the client request required authentication for external
	///access, then the server MUST set the value of this variable from the
	///'auth-scheme' token in the request Authorization header field.
	///But in our case we didn't need an authentication so the AUTH_TYPE is empty (RFC3875)
	// env.push_back("AUTH_TYPE=");

	///SERVER_SOFTWARE: The name and version of the server software that is answering the client request.
	// env.push_back("SERVER_SOFTWARE=WEBSERV/1.1");

	///SERVER_NAME: The server's hostname or IP address.
	///Because we work in HTTP/1.1 the SERVER_NAME is the host in the requete but there is the PORT after him.
	///So we seperate the twoo to have the good implementation of environnement.
	tmp = _header.find("Host:")->second;
	env.push_back("SERVER_NAME=" + tmp.substr(0, tmp.find(":")));

	///GATEWAY_INTERFACE:The revision of the Common Gateway Interface the server uses.
	env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	/*------------------------------------------------------------------------------------------------------*/

	/*-----------------------------------REQUETE_INFORMATION------------------------------------------------*/

	///SERVER_PROTOCOL:The name and revision of the information protocol the request came in with.
	///By default in this subject we just use HTTP/1.1
	env.push_back("SERVER_PROTOCOL=HTTP/1.1");

	///SERVER_PORT: The port number of the host on which the server is running.
	///It's not always in the requete but in HTTP/1.1 it's an obligation to have
	///the port in the requete after the host
	env.push_back("SERVER_PORT=" + tmp.substr(tmp.find(":")+1));

	///REQUEST_METHOD:The method with which the information request was issued (e.g., GET, POST, HEAD).
	env.push_back("REQUEST_METHOD=" + _header.at("Method:"));//probleme car pour le moment je renvoie la methid de la config

	///PATH_INFO:Extra path information passed to a CGI program.
	///ATTENTION voir si pas un probleme avec le testeur de l'école mais pour le moment ça suit la RFC
	// if (_header.at("Method:") == "GET")
	// 	env.push_back("PATH_INFO=" + _config.url.substr(_config.url.find("?") + 1));
	// else
	// 	env.push_back("PATH_INFO=");

	///PATH_TRANSLATE: The translated version of the path given by the variable PATH_INFO.
	///See with the PATH_INFO and it's just ok when it's a POST
	getcwd(tmp_path, PATH_MAX);
	env.push_back(std::string ("PATH_TRANSLATE=") + tmp_path + "/" + _config.path.substr(2));

	///SCRIPT_NAME:The virtual path (e.g., /cgi-bin/program.pl ) of the script being executed.
	if (_header.at("Method:") == "GET")
		env.push_back("SCRIPT_NAME=" + _config.url.substr(1, _config.url.find("?") - 1));
	///TO DO SCRIPT NAME with post have a "/" en trop
	// else
	// 	env.push_back("SCRIPT_NAME=" + _config.url);

	///QUERY_STRING: The query information passed to the program.
	///It is appended to the URL following a question mark (?).
	///TO DO problem de reception de la query string lors du post
	///RM : The server MUST set this variable; if the Script-URI does not include
	///a query component, the QUERY_STRING MUST be defined as an empty
	///string ("").
	if (_config.url.find("?") != std::string::npos)
		env.push_back("QUERY_STRING=" + _config.url.substr(_config.url.find("?") + 1));
	///TO DO pas de query string lors du post
	/// else
	/// 	env.push_back("QUERY_STRING=" + _body);

	///REMOTE_HOST:The hostname from which the user is making the request.
	///TO DO ve2rification de pourquoi j'ai pas d'argument
	// env.push_back("REMOTE_HOST=");

	///CONTENT_TYPE
	if (_header.at("Method:") == "POST")
		env.push_back("CONTENT_TYPE=" + _header.at("Content-Type:"));

	///CONTENT_LENGTH: The length of the query data (in bytes or the number of characters) passed to the CGI program through standard input.
	if (_header.at("Method:") == "POST")
		env.push_back("CONTENT_LENGTH=" + ft_to_string(_contentlenght));
	else
		env.push_back("CONTENT_LENGTH=");


	/*------------------------------------------------------------------------------------------------------*/

	/*------------------------------------CLIENT_INFORMATION------------------------------------------------*/

	///HTTP_ACCEPT:A list of the media types the client can accept.
	///In the request it is the Accept:
	env.push_back("HTTP_ACCEPT=" + _header.at("Accept:"));


	///HTTP_ACCEPT_LANGUAGE:A list of the language the client can accept(understand).
	///In the request it is the ACCEPT-Language:
	env.push_back("HTTP_ACCEPT_LANGUAGE=" + _header.at("Accept-Language:"));

	///HTTP_USER_AGENT:The User-Agent request-header field contains information about the user agent
	///originating the request. It is a name of the web browser.
	env.push_back("HTTP_USER_AGENT=" + _header.at("User-Agent:"));

	///HTTP_COOKIE: A list of cookies defined for that URL.
	///ASK TO DO if we integrate cookie to the website.

	///HTTP_REFERER:The URL of the document the client points to before accessing the CGI program.
	env.push_back("HTTP_REFERER=" + _header.at("Referer:"));
	/*------------------------------------------------------------------------------------------------------*/
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


void	responce::child_process(int *fd_in, int *fd_out, char **env)
{
	// dup2(fd_out[0], STDIN_FILENO);
	// dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in[0], STDIN_FILENO);
	dup2(fd_out[1], STDOUT_FILENO);
	close(fd_in[0]);
	close(fd_in[1]);
	close(fd_out[0]);
	close(fd_out[1]);


	char *av[3];
	std::string	tmp = "cgi-bin" + _config.path.substr(_config.path.rfind("/"));
	if (tmp.find("?") != std::string::npos)
	{
		tmp.erase(tmp.find("?"));
	}
	///TO Do a changer en fonction du langage
	std::string pyth = "/usr/bin/python2.7";

	av[0] = (char *)pyth.c_str();
	av[1] = (char *)tmp.c_str();
	av[2] = NULL;
	// std::cout << "@@@@" << std::endl;
	// std::cout << "AV[0] |" << av[0] << "|" << std::endl;
	// std::cout << "AV[1] |" << av[1] << "|" << std::endl;
	// std::cout << "@@@@" << std::endl;

	///TO DO error if the execve fail
	execve(av[0], av, env);
	//perror("The error post exec is :");
	exit(1);
}

std::string	responce::parent_process(pid_t pid, int *fd_in, int *fd_out, int status)
{
	char			tmp[101] = {0};
	std::string		str_return;
	int ret = 1;


	 waitpid(pid, &status, 0);
	//wait(0);

	// int	ret = read(fd_out[0], tmp, 100);
	// str_return += std::string(tmp);
	while (ret > 0)
	{
		ret = read(fd_out[0], tmp, 100);
		tmp[ret] = '\0';
		str_return += std::string(tmp);
	}
	close(fd_out[0]);
	std::cout << "ICI : " << str_return << std::endl;
	return str_return;
}

std::string	responce::cgi_execute()
{
	///TO DO avant il faut vérifier : do it with fstream
	char	**env = vec_to_char(cgi_env());
	int		fd_in[2]; //body
	int		fd_out[2]; //family
	pid_t	pid;
	int		status;

	if (pipe(fd_in) == -1)
		std::cerr << "CGI : Le pipe du FD_IN a foiré" << std ::endl;
	if(pipe(fd_out) == -1)
		std::cerr << "CGI : Le pipe du FD_body a foiré" << std ::endl;

	pid = fork();
	if (pid == -1)
		std::cerr << "CGI : Le fork il a foiré" << std::endl;

	else if (pid == 0)
	{
		// std::cout << "/////////////" << std::endl;
		//for (size_t i = 0; env[i]; i++)
		// std::cout << "|" << env[i] << "|" << std::endl;
		// std::cout << "/////////////" << std::endl;
		child_process(fd_in, fd_out, env);
	}

	dup2(fd_in[0], 0);
	if (_config.method == "POST")
		write(fd_in[1], _body.c_str(), _body.size());
	//close(fd[0]); Niop
	close(fd_in[1]);
	close(fd_in[0]);

	//close(fd_out[0]); on va read dessus
	close(fd_out[1]);





	return parent_process(pid, fd_in, fd_out, status);
}
