CC = cc
CFLAGS += -Werror -Wall -Wextra -MMD -g3

LIBFT_DIR = ./libft
LIBFT = libft.a
LIB = -L$(LIBFT_DIR) -lft

NAME = push_swap
BONUS = checker

SRCS += push_swap.c \
	./utils/check_args.c \
	./utils/ft_stc.c \
	./utils/stack.c \
	./utils/instruct.c \
	./utils/sort.c

B_SRCS += checker_bonus.c \
	./utils/check_args.c \
	./utils/ft_stc.c \
	./utils/stack.c \
	./utils/instruct.c \
	./utils_bonus/orders_bonus.c \

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

B_OBJS = $(B_SRCS:.c=.o)
B_DEPS = $(B_SRCS:.c=.d)

all	:	$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) : 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME)	: $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIB)

$(BONUS) : $(LIBFT) $(B_OBJS)
	$(CC) -o $(BONUS) $(B_OBJS) $(LIB)

clean	:                 
		rm -f $(OBJS) $(B_OBJS) $(DEPS) $(B_DEPS)
		$(MAKE) -C $(LIBFT_DIR) clean

fclean	:	clean
		rm -f $(NAME) $(BONUS)
		$(MAKE) -C $(LIBFT_DIR) fclean
		
re	:	fclean all        

.PHONY: all clean fclean re
-include DEPS
