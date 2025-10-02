CC = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = fragtrap

SRCS += main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp

OBJS = $(SRCS:.cpp=.o)

COLOR = \e[33m
RESET = \e[0m

all	: $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@printf "$(COLOR)▗▄▄▄▖▗▖  ▗▖▄▀▀▚▖▄▄▄▄\n"
	@printf 	    "▐▌    ▝▚▞▘ █  ▐▌   █\n"
	@printf 	    "▐▛▀▀▘  ▐▌  █  ▐▌█▀▀▀\n"
	@printf 	    "▐▙▄▄▖▗▞▘▝▚▖▀▄▄▞▘█▄▄▄\n$(RESET)"

clean	:
	@rm -f $(OBJS)
	@printf "> Ojects        ❌\n"

fclean	:	clean
	@rm -f $(NAME)
	@printf "> Executable    ❌\n"

re	:	fclean all

.PHONY: all clean fclean re
