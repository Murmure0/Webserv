#pragma once

#include <iostream>
#include <istream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <linux/limits.h>

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