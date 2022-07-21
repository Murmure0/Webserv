
#include "../../includes/webserv.hpp"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s)
{
	return rtrim(ltrim(s));
}

std::string file_to_string(std::string file_path)
{
	std::ifstream t(file_path.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void print_line(t_config line)
{
	std::cout << "Key: " << line.key << std::endl;
	std::cout << "Value: " << line.value.substr(0, 50) << std::endl;
	std::cout << "e-----------------e" << std::endl;
}

t_config get_next_variable(std::string str)
{
	std::istringstream f(str);
	std::string line;
	t_config config;

	config.next_start = 0;

	if (trim(str).empty())
		return config;

	if (!std::getline(f, line))
	{
		return config;
	}

	while (trim(line).empty())
	{
		std::getline(f, line);
		config.next_start++;
	}

	config.next_start += line.length() + 1;
	if (line.find_first_of('{') == std::string::npos)
	{
		config.key = trim(line.substr(0, line.find_first_of(' ')));
		if (line.find_first_of(' ') != std::string::npos)
			config.value = trim(line.substr(line.find_first_of(' ')));
	}
	else
	{
		size_t bracket_level = 1;
		config.key = trim(line.substr(0, line.find_first_of(' ')));
		config.before_braquet = trim(line.substr(line.find_first_of(' '), line.find_first_of('{') - line.find_first_of(' ')));
		while (bracket_level != 0 && std::getline(f, line))
		{
			config.next_start += line.length() + 1;
			if (line.find_first_of('{') != std::string::npos)
			{
				bracket_level += 1;
			}
			if (line.find_first_of('}') != std::string::npos)
			{
				bracket_level -= 1;
			}
			if (bracket_level != 0)
				config.value += line + "\n";
		}
	}
	return config;
}