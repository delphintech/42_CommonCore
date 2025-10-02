CC = c++ -g3

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = fixed

SRCS += main.cpp Fixed.cpp

OBJS = $(SRCS:.cpp=.o)

COLOR = \e[35m
RESET = \e[0m

all	: $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@printf "$(COLOR)▗▄▄▄▖▗▖  ▗▖▄▀▀▚▖▄▀▀▚▖\n"
	@printf 	    "▐▌    ▝▚▞▘ █  ▐▌█  ▐▌\n"
	@printf 	    "▐▛▀▀▘  ▐▌  █  ▐▌█  ▐▌\n"
	@printf 	    "▐▙▄▄▖▗▞▘▝▚▖▀▄▄▞▘▀▄▄▞▘\n$(RESET)"

clean	:
	@rm -f $(OBJS)
	@printf "> Ojects        ❌\n"

fclean	:	clean
	@rm -f $(NAME)
	@printf "> Executable    ❌\n"

re	:	fclean all

.PHONY: all clean fclean re
