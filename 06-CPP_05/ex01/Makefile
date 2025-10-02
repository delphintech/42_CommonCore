CC = c++

FLAGS = -Wall -Werror -Wextra -MMD -std=c++98

NAME = form

SRCS += main.cpp Bureaucrat.cpp Form.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

COLOR = \e[90m
RESET = \e[0m

all	: $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@printf "$(COLOR)▗▄▄▄▖▗▖  ▗▖▄▀▀▚▖█\n"
	@printf 	    "▐▌    ▝▚▞▘ █  ▐▌█\n"
	@printf 	    "▐▛▀▀▘  ▐▌  █  ▐▌█\n"
	@printf 	    "▐▙▄▄▖▗▞▘▝▚▖▀▄▄▞▘█\n$(RESET)"

clean	:
	@rm -f $(OBJS) $(DEPS)
	@printf "> Ojects        ❌\n"

fclean	:	clean
	@rm -f $(NAME)
	@printf "> Executable    ❌\n"

re	:	fclean all

.PHONY: all clean fclean re

-include DEPS