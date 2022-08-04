
NAME = webserv

CC = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -rf

SOURCES = 	./src/parsing_main.cpp \
			./src/server/location.cpp \
			./src/server/server.cpp \
			./src/server/webserv.cpp \
			./src/sockets/listen_socket.cpp \
			./src/utils/config_parsing.cpp \
			./src/utils/url_manipulation.cpp \
			./src/utils/running_server/setup_server.cpp \
			./src/utils/running_server/handle_client_connection.cpp \
			./src/http/request.cpp \
			./src/http/responce.cpp \
			./src/cgi/cgi.cpp \
			./includes/ft.cpp \


OBJECTS = $(SOURCES:%.cpp=%.o)

all :		$(NAME)

$(NAME):	$(OBJECTS)
		@$(CC)  $(OBJECTS) -o $(NAME)
		@echo "[\033[32m$(NAME) ready to use\033[0m]"


clean:
		@$(RM) $(OBJECTS)
		@echo "[\033[32m$(NAME) files cleaned !\033[0m]"

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
