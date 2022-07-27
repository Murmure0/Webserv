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

//#ifdef __linux
//#include <linux/limits.h>
// #elif __APPLE__
// #include <limits.h>
// #endif

#define BUFFER_SIZE 65536

typedef struct config
{
	std::string url;
	std::string method;
	std::string path;
	std::string root;
	std::string index;
	size_t max_body_size;
	bool autoindex;
	std::string header;
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

int setup_server(int port, int backlog, sockaddr_in sockaddr);
int accept_new_connection(int server_fd);

std::string ft_to_string(size_t i);

std::string complete_url(std::string base_url, std::string to_add);
std::string ltrim(const std::string &s, const std::string &set);
std::string rtrim(const std::string &s, const std::string &set);
std::string trim(const std::string &s, const std::string &set);
bool compare_url(std::string url1, std::string url2);

#include "../src/http/request.hpp"
#include "../src/http/responce.hpp"