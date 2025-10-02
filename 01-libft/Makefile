CC = cc

CFLAGS += -Werror -Wall -Wextra -MMD

NAME = libft.a

SRC_NAME = ft_isalpha \
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
	ft_putnbr_fd

SRCS = $(addsuffix .c,$(SRC_NAME))

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all	:
	@make $(NAME)
	
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME)	:	$(OBJS)
	ar crs $(NAME) $(OBJS)

clean	:                 
	rm -f $(OBJS) $(BONUS_OBJS) $(DEPS) $(BONUS_DEPS)

fclean	:	clean
	rm -f $(NAME)
		
re	:	fclean all

BONUS_NAME = ft_lstnew \
	ft_lstadd_front \
	ft_lstsize \
	ft_lstlast \
	ft_lstadd_back \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap

BONUS_SRCS = $(addsuffix _bonus.c,$(BONUS_NAME))

BONUS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_DEPS = $(BONUS_SRCS:.c=.d)

$(BONUS_OBJS): $(BONUS_SRCS)
	$(CC) $(CFLAGS) -c $(BONUS_SRCS)

bonus : $(OBJS) $(BONUS_OBJS)
	ar crs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re
-include $(DEPS) $(BONUS_DEPS)