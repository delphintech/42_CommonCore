#################### SETUP ####################
NAME = webserv
CC = clang++

FLAGS = -Wall -Wextra -Werror -MMD -g3
CPPFLAG = -std=c++98

#################### PATH ####################
SRC_PATH = src/
OBJ_PATH = obj/
DEP_PATH = deps/

#################### SRC & OBJ ####################
SRC =	main.cpp \
		class/Client.cpp \
		class/Config.cpp \
		class/Server.cpp \
		class/Location.cpp \
		class/DomainConfig.cpp \
		class/Socket.cpp \
		class/PollManager.cpp \
		class/File.cpp \
		response/AHTTPResponse.cpp \
		response/ErrorResponse.cpp \
		response/ChunkedResponse.cpp \
		response/Response.cpp \
		handler/ErrorHandler.cpp \
		request/Request.cpp \
		request/AHTTPRequest.cpp \
		request/AHTTPChunkedRequest.cpp \
		request/AMultipartRequest.cpp \
		responseFactory/CgiResponseHandler.cpp \
		responseFactory/DirectoryListerResponseHandler.cpp \
		responseFactory/StaticFileResponseHandler.cpp \
		middleware/MiiddlewareChain.cpp \
		middleware/ParseRequestHandlerMiddleware.cpp \
		middleware/BodyRequestMiddleware.cpp \
		middleware/ContentResponseFactoryMiddleWare.cpp \
		middleware/HttpIsAllowedMethodMiddleware.cpp \
		middleware/PathResolverMiddleware.cpp \
		Utils/Utils.cpp \
		Utils/System/System.cpp \
		Utils/Path/Path.cpp \
		Utils/String/String.cpp \
		parseFormData/MultipartFormDataParser.cpp \
		parseFormData/OtherParser.cpp

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
DEP = $(OBJS:.o=.d)

#################### HEADERS ####################
INCLUDES = -I ./includes

# Dépendances générées par -MMD
DEPS := $(OBJS:.o=.d)
#################### RULES ####################
all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@$(CC) $(FLAGS) $(CPPFLAG) $(INCLUDES) -c $< -o $@

$(OBJ_PATH) :
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)class
	@mkdir $(OBJ_PATH)response
	@mkdir $(OBJ_PATH)test
	@mkdir $(OBJ_PATH)handler
	@mkdir $(OBJ_PATH)request
	@mkdir $(OBJ_PATH)responseFactory
	@mkdir $(OBJ_PATH)middleware
	@mkdir $(OBJ_PATH)Utils
	@mkdir $(OBJ_PATH)Utils/System
	@mkdir $(OBJ_PATH)Utils/Path
	@mkdir $(OBJ_PATH)Utils/String
	@mkdir $(OBJ_PATH)parseFormData

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@printf "\n"
	@printf "\t404 Error not found\n"
	@printf "\n"
	@printf "|---------------------------------------------------------------|\n"
	@printf "|              _                        ______________________  |\n"
	@printf "|             | |                      |     404 Not Found    | |\n"
	@printf "|             | |===( )   //////       |________    __________| |\n"
	@printf "|             |_|   |||  | o o|                 \  /            |\n"
	@printf "|                    ||| ( c  )                  ____           |\n"
	@printf "|                     ||| \= /                  ||   \_         |\n"
	@printf "|                      ||||||                   ||     |        |\n"
	@printf "|                      ||||||                ...||__/|-         |\n"
	@printf "|                      ||||||             __|________|__        |\n"
	@printf "|                        |||             |______________|       |\n"
	@printf "|                        |||             || ||      || ||       |\n"
	@printf "|                        |||             || ||      || ||       |\n"
	@printf "|------------------------|||-------------||-||------||-||-------|\n"
	@printf "|                        |___>           || ||      || ||       |\n"
	@printf "|---------------------------------------------------------------|\n"
	@printf "\n"
	
clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)
	@rm -rf /tmp/webserv

re: fclean all

.PHONY: all clean fclean re

-include DEPS

#################### RULES ####################
run: all
	./$(NAME) config_file

val:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(NAME)

#nbrigui Test

test: all
	bash ./bin/multiWindows.sh

clearTmp:
	rm -rf *.tmp
	rm ./logs/access.log

runnbrigui: all
	./$(NAME) ./conf.d/nbrigui.conf

eval: all
	./$(NAME) ./conf.d/eval.conf