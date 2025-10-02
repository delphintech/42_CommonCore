CC = c++

FLAGS = -Wall -Werror -Wextra -std=c++98 

NAME = megaphone

SRCS += megaphone.cpp

OBJS = $(SRCS:.cpp=.o)

GREEN = \e[32m
RESET = \e[0m

all	: $(NAME)
		
%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@printf "$(GREEN)▗▄▄▄▖▗▖  ▗▖▄▀▀▚▖▄▀▀▚▖\n"
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
