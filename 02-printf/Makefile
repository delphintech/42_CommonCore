CC = cc

CFLAGS += -Werror -Wall -Wextra -MMD -g3

NAME = libftprintf.a

SRCS += ft_printf.c \
		print_alpha.c \
		print_hexa.c \
		utils/ft_itoa.c \
		utils/ft_strlen.c 

OBJS += $(SRCS:.c=.o)
DEPS += $(SRCS:.c=.d)

all	:	$(NAME)

%.o: %.c	$(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $< 
	
$(NAME)	:	$(OBJS) $(SRCS)
	ar crs $(NAME) $(OBJS)

clean	:                 
		rm -f $(OBJS) $(DEPS)

fclean	:	clean
		rm -f $(NAME)
		
re	:	fclean all
	
.PHONY: all clean fclean re

-include DEPS

tclean	:	clean
		rm -f $(NAME) *.d *.o test

test : 	$(NAME) test.c
	$(CC) $(CFLAGS) -c test.c 
	$(CC) $(CFLAGS) -o test test.o $(OBJS) 