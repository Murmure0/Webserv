#include "../http/responce.hpp"

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

void	responce::print_the_header()
{
	std::cout << "*********************************" << std::endl;
	for (std::map<std::string, std::string>::iterator i = _header.begin(); i != _header.end(); i++)
	{
		std::cout << i->first;
		std::cout << "|" << i->second << "|" ;
		std::cout << std::endl;
	}
	std::cout << "*********************************" << std::endl;
}

std::vector<std::string>	responce::cgi_env()
{
	std::vector<std::string>	env;
	std::string					tmp;
	char						tmp_path[PATH_MAX];
	/*-----------------------------------SERVER_INFORMATION-------------------------------------------------*/

	///AUTH_TYPE:The authentication method used to validate a user.
	///For HTTP, if the client request required authentication for external
	///access, then the server MUST set the value of this variable from the
	///'auth-scheme' token in the request Authorization header field.
	///But in our case we didn't need an authentication so the AUTH_TYPE is empty (RFC3875)
	env.push_back("AUTH_TYPE=");

	///SERVER_SOFTWARE: The name and version of the server software that is answering the client request.
	env.push_back("SERVER_SOFTWARE=WEBSERV/1.1");

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
	if (_header.at("Method:") == "GET")
		env.push_back("PATH_INFO=" + _config.url.substr(_config.url.find("?") + 1));
	else
		env.push_back("PATH_INFO=");

	///PATH_TRANSLATE: The translated version of the path given by the variable PATH_INFO.
	///See with the PATH_INFO and it's just ok when it's a POST
	getcwd(tmp_path, PATH_MAX);
	env.push_back(std::string ("PATH_TRANSLATE=") + tmp_path + "/" + _config.path.substr(2));

	///SCRIPT_NAME:The virtual path (e.g., /cgi-bin/program.pl ) of the script being executed.
	if (_header.at("Method:") == "GET")
		env.push_back("SCRIPT_NAME=" + _config.url.substr(1, _config.url.find("?") - 1));
	else
		env.push_back("SCRIPT_NAME=" + _config.url);

	///QUERY_STRING: The query information passed to the program.
	///It is appended to the URL following a question mark (?).
	if (_config.url.find("?") != std::string::npos)
		env.push_back("QUERY_STRING=" + _config.url.substr(_config.url.find("?") + 1));

	///REMOTE_HOST:The hostname from which the user is making the request.
	env.push_back("REMOTE_HOST=");


	///CONTENT_TYPE
	env.push_back("CONTENT_TYPE=" + _current_mime);

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
	char	**env;
	int		it = 0;

	env = new char*[vec_env.size() + 1];
	for (std::vector<std::string>::iterator i = vec_env.begin(); i != vec_env.end(); i++, it++)
	{
		env[it] = i->c_str();
	}

}

std::string	responce::cgi_execute()
{
	std::vector<std::string>	vec_env = cgi_env();
	char						**env;

	return "coucou";
}
