CC = cc
CFLAGS += -Werror -Wall -Wextra -MMD

LIBFT_DIR = ./libft
LIBFT = libft.a
LIB = -L$(LIBFT_DIR) -lft

NAME = pipex

SRCS += pipex.c \
	./utils/utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

BSRCS += pipex_bonus.c \
	./utils/utils.c \
	./utils/utils_bonus.c

BOBJS = $(BSRCS:.c=.o)
BDEPS = $(BSRCS:.c=.d)

all	:	$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) : 
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) $(LIBFT)

$(NAME)	: $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIB)

bonus	: $(LIBFT) $(BOBJS)
	$(CC) -o $(NAME) $(BOBJS) $(LIB)

clean	:
	rm -f $(OBJS) $(BOBJS) $(DEPS) $(BDEPS) $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean	:	clean
		rm -f $(NAME) $(LIBFT)
		$(MAKE) -C $(LIBFT_DIR) fclean

re	:	fclean all

.PHONY: all clean fclean re
-include DEPS

