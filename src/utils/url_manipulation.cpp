#include "../../includes/webserv.hpp"

std::string complete_url(std::string base_url, std::string to_add)
{
	if (base_url.find_last_of("/") != base_url.size())
	{
		return base_url + "/" + to_add;
	}
	return base_url + to_add;
}

std::string ltrim(const std::string &s, const std::string &set)
{
	size_t start = s.find_first_not_of(set);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s, const std::string &set)
{
	size_t end = s.find_last_not_of(set);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s, const std::string &set)
{
	return rtrim(ltrim(s, set), set);
}