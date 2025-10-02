CC = c++ -g3

FLAGS = -Wall -Werror -Wextra -std=c++98 -g3

NAME = fight

SRCS += main.cpp Weapon.cpp HumanA.cpp HumanB.cpp

OBJS = $(SRCS:.cpp=.o)

COLOR = \e[34m
RESET = \e[0m

all	: $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@printf "$(COLOR)▗▄▄▄▖▗▖  ▗▖▄▀▀▚▖▄▄▄▄\n"
	@printf 	    "▐▌    ▝▚▞▘ █  ▐▌   █\n"
	@printf 	    "▐▛▀▀▘  ▐▌  █  ▐▌▀▀▀█\n"
	@printf 	    "▐▙▄▄▖▗▞▘▝▚▖▀▄▄▞▘▄▄▄█\n$(RESET)"

clean	:
	@rm -f $(OBJS)
	@printf "> Ojects        ❌\n"

fclean	:	clean
	@rm -f $(NAME)
	@printf "> Executable    ❌\n"

re	:	fclean all

.PHONY: all clean fclean re
