CC = cc
CFLAGS += -Werror -Wall -Wextra -MMD -pthread -fsanitize=thread

NAME = philo

SRCS += main.c \
	utils/ft_atoi.c \
	utils/life.c \
	utils/state.c \
	utils/struct_fork.c \
	utils/struct_philo.c \
	utils/utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all	:	$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean	:
	rm -f $(OBJS) $(DEPS)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all

.PHONY: all clean fclean re
-include DEPS
