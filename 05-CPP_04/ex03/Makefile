CC = c++ -g3

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = materia

SRCS += main.cpp AMateria.cpp Cure.cpp Ice.cpp Character.cpp MateriaSource.cpp

OBJS = $(SRCS:.cpp=.o)

COLOR = \e[92m
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
