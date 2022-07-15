
NAME = webserv

CC = c++

CXXFLAGS =

RM = rm -rf

SOURCES = 	./src/parsing_main.cpp \
			./src/server/location.cpp \
			./src/server/server.cpp \
			./src/server/webserv.cpp \
			./src/utils/config_parsing.cpp \
			./src/utils/running_server/setup_server.cpp \
			./src/utils/running_server/handle_client_connection.cpp \


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