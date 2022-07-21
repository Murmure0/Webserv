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

#ifdef __linux
#include <linux/limits.h>
#elif __APPLE__
#include <limits.h>
#endif

#define BUFFER_SIZE 65536

#include "../src/http/request.hpp"
#include "../src/http/responce.hpp"

typedef struct config
{
	std::string _method;
	std::string _path;
	size_t _max_body_size;
	bool _autoindex;
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
void handle_connection(int client_socket);

std::string ft_to_string(size_t i);