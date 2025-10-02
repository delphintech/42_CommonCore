############# SET UP #############

CC = cc
NAME = libft.a
OPTION = -c
FLAG = -Wall -Werror -Wextra

#################### PATH ####################

SRC_PATH	= src/
FILE_PATH	= file/
LST_PATH	= lst/
MEM_PATH	= mem/
STR_PATH	= str/
CHECK_PATH	= check/
NBR_PATH	= nbr/
FT_PRINTF_P	= ft_printf/
GNL_PATH	= gnl/
INCLD		= -Iincludes

#################### SRC & OBJ ####################

FILE		=	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putnbr_base_fd.c
LST			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
				ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
				ft_lstnew.c ft_lstsize.c
MEM			=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
				ft_calloc.c ft_memchr.c ft_memcmp.c
STR			=	ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
				ft_toupper.c ft_tolower.c ft_strlen.c\
				ft_strchr.c ft_strrchr.c ft_strncmp.c \
				ft_strdup.c ft_substr.c	ft_strjoin.c \
				ft_strtrim.c ft_split.c \
				ft_strmapi.c ft_striteri.c
CHECK		=	ft_isspace.c ft_isalpha.c ft_isdigit.c \
				ft_isalnum.c ft_isascii.c ft_isprint.c ft_charcmp.c
NBR			=	ft_atoi.c ft_itoa.c ft_intlen_base.c
FT_PRINTF	=	ft_printf.c ft_printf_utils.c
GNL			=	get_next_line.c get_next_line_utils.c

SRC 		= 	$(addprefix $(FILE_PATH), $(FILE)) \
				$(addprefix $(LST_PATH), $(LST)) \
				$(addprefix $(MEM_PATH), $(MEM)) \
				$(addprefix $(STR_PATH), $(STR)) \
				$(addprefix $(CHECK_PATH), $(CHECK)) \
				$(addprefix $(NBR_PATH), $(NBR)) \
				$(addprefix $(FT_PRINTF_P), $(FT_PRINTF)) \
				$(addprefix $(GNL_PATH), $(GNL))
SRCS		= 	$(addprefix $(SRC_PATH), $(SRC))

OBJS 		=	${SRCS:.c=.o}

#################### RULES ####################

all : $(NAME)

clean:
	@rm -rf $(OBJS)
	@echo "\033[1;36m----------- LIBFT OBJ CLEANED -----------\033[0;29m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;36m----------- LIBFT.A CLEANED -----------\033[0;29m"
	
re: fclean all

rebonus: fclean

#################### COMPILATION ####################

# MANDATORY

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(FLAG) -c $< -o $@

.SILENT: all clean fclean re $(OBJS)
.PHONY: all clean fclean re
