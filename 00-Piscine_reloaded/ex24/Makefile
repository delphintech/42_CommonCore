# Compiler
CC = gcc

# Flag compiler
CFLAGS += -Werror -Wall -Wextra

# Debug flags
DBGFLAGS := -g

# Include header files from another directory
INCLUDES = -I "/includes"

# Nom du programme
NAME = libft.a

# Liste des sources

SRC_DIR	= srcs
SRCS	= $(addprefix $(SRC_DIR)/, \
	ft_putchar.c \
	ft_putstr.c \
	ft_strcmp.c \
	ft_strlen.c \
	ft_swap.c \
)

# Liste des ojets
OBJS = $(SRCS:.c=.o)

all	:
		@make $(NAME)

$(NAME)	:	$(OBJS)
		ar crs $(NAME) $(OBJS)

clean	:                 
		rm -f $(OBJS)				## Supprime les .o
		@$(CLEAN)           ## Supprime les ~

fclean	:	clean					## Appelle la precedente puis supprime l'executable.
		rm -f $(NAME)
		
re	:	fclean all        ## Supprime tout et recompile tout

debug :               ## Permet de debuger le code avec lldb
	$(CC) -o $(NAME) -${DBGFLAGS} $(SRCS)
	
## Empèche Makefile d'associer le nom de ses règles à un fichier s'il en existe un 
## à leur nom dans le directory
.PHONY: all clean fclean re