#include "../http/responce.hpp"

/*Fonction utile au CGI car elle permet lors de l'initialisation de la re2ponse, de transformer le header
de la requete qui est en std::string en map<std::string, std::string>*/
std::map<std::string, std::string>	responce::header_to_map(std::string str)
{
	std::map<std::string, std::string>	map_header;
	std::string	value;
	std::string	key;

	str.erase(0, str.find('\n')+1);
	while (!str.empty())
	{
		key = str.substr(0, str.find(":")+1);
		value = str.substr(str.find(" ")+1, str.find('\n') - 1 -(str.find(":") + 1));
		str.erase(0, str.find('\n')+1);
		if (str.find('\n') == std::string::npos)
		{
			value = str.substr(str.find(" ")+1, str.find('\r') - 1 -(str.find(":") + 1));
			str.clear();
		}
		map_header.insert(std::make_pair(key, value));
	}
	return (map_header);
}

std::vector<std::string>	responce::cgi_env()
{
	std::vector<std::string>	env;

	///CONTENT_TYPE
	env.push_back("CONTENT_TYPE=" + _current_mime);

	///HTTP_USER_AGENT:The User-Agent request-header field contains information about the user agent
	///originating the request. It is a name of the web browser.
	env.push_back("HTTP_USER_AGENT=" + _header.at("User-Agent:"));
	for(std::vector<std::string>::iterator i = env.begin(); i != env.end(); i++)
		std::cout << *i << std::endl;

	///CONTENT_LENGHT:The length of the query information that is available only for POST requests.
	///TO DO when we do cgi for POST
	return env;
}

std::string	responce::cgi_execute()
{
	std::vector<std::string>	vec_env = cgi_env();

	return "coucou";
}
