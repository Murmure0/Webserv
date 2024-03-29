#pragma once

#include <iostream>
#include <istream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <algorithm>
#include <csignal>
#include <cstdlib>
#include <dirent.h>
#include <utility>
#include <sys/types.h>
#include <arpa/inet.h>

//#ifdef __linux
//#include <linux/limits.h>
// #elif __APPLE__
// #include <limits.h>
// #endif

#define BUFFER_SIZE 65536
#define SEND_BUFFER_SIZE 65536

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef struct config
{
	std::string url;
	std::string method;
	std::string path;
	std::string root;
	std::string index;
	std::string redirect;
	size_t max_body_size;
	bool autoindex;
	std::string header;
	std::map<std::string, std::string> error_pages;
} t_responce_config;

typedef struct config_parsing
{
	std::string key;
	std::string value;
	std::string before_braquet;
	size_t next_start;
} t_config;

std::string file_to_string(std::string file_path);
config_parsing get_next_variable(std::string str);
void print_line(t_config line);

std::string ft_to_string(size_t i);

std::string complete_url(std::string base_url, std::string to_add);
std::string ltrim(const std::string &s, const std::string &set);
std::string rtrim(const std::string &s, const std::string &set);
std::string trim(const std::string &s, const std::string &set);
std::map<std::string, std::string> set_errors(std::map<std::string, std::string> *server_errors, std::map<std::string, std::string> *location_errors);
bool compare_url(std::string url1, std::string url2);
void welcome(void);
void bye(void);

#include "../src/http/request_config.hpp"
#include "../src/http/request.hpp"
#include "../src/http/responce.hpp"
