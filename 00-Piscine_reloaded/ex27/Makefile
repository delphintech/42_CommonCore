# Compiler
CC = gcc

# Flag compiler
CFLAGS += -Werror -Wall -Wextra

# Debug flags
DBGFLAGS := -g

# Nom du programme
NAME = ft_display_file

# Liste des sources
SRCS = ft_display_file.c

# Liste des ojets
OBJS = $(SRCS:.c=.o)

all	:
	@make $(NAME)

$(NAME)	:	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean	:                 
	rm -f $(OBJS)
	@$(CLEAN)

fclean	:	clean
	rm -f $(NAME)

re	:	fclean all

debug :
	$(CC) -o $(NAME) -${DBGFLAGS} $(SRCS)

.PHONY: all clean fclean re 