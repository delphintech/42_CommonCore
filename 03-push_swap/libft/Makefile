CC = cc

CFLAGS += -Werror -Wall -Wextra -MMD -g3

NAME = libft.a

SRC_NAME += ft_isalpha \
	ft_isdigit \
	ft_toupper \
	ft_tolower \
	ft_isalnum \
	ft_isascii \
	ft_strchr \
	ft_isprint \
	ft_strrchr \
	ft_strlen \
	ft_strncmp \
	ft_memset \
	ft_bzero \
	ft_memchr \
	ft_memcpy \
	ft_memcmp \
	ft_memmove \
	ft_strnstr \
	ft_strlcpy \
	ft_strlcat \
	ft_atoi \
	ft_calloc \
	ft_strdup \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_split \
	ft_itoa \
	ft_strmapi \
	ft_striteri \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd \
	ft_lstnew_bonus \
	ft_lstadd_front_bonus \
	ft_lstsize_bonus \
	ft_lstlast_bonus \
	ft_lstadd_back_bonus \
	ft_lstdelone_bonus \
	ft_lstclear_bonus \
	ft_lstiter_bonus \
	ft_lstmap_bonus \
	get_next_line \
	./get_next_line_utils/get_next_line_utils \
	get_next_line_bonus \
	./get_next_line_utils/get_next_line_utils_bonus \
	ft_printf \
	./ft_printf_utils/print_alpha \
	./ft_printf_utils/print_hexa

SRCS = $(addsuffix .c,$(SRC_NAME))

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all	:	$(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	ar crs $(NAME) $(OBJS)

clean	:                 
	rm -f $(OBJS) $(DEPS)

fclean	:	clean
	rm -f $(NAME)
		
re	:	fclean all

.PHONY: all clean fclean re
-include $(DEPS) $(BONUS_DEPS)
