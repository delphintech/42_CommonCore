FILE = 42

CC = cc
CFLAGS += -Werror -Wall -Wextra -MMD

LIBFT_DIR = ./libft
LIBFT = libft.a

MLX = ./minilibx

LIB_FLAG = $(LIBFT_DIR)/$(LIBFT) -L$(MLX) -lmlx -lXext -lX11 -lm
LIBS = .libs

NAME = fdf

SRCS += fdf.c \
	utils/utils.c \
	utils/coords.c \
	utils/events_bonus.c \
	utils/events.c \
	utils/struct.c \
	utils/draw.c \
	utils/color.c \
	utils/map.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all	:	$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS) :
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX)
	touch $@

$(NAME)	: $(LIBS) $(OBJS) | $(LIBS)
	$(CC) -o $(NAME) $(OBJS) $(LIB_FLAG)

clean	:
	rm -f $(OBJS) $(DEPS) $(LIBFT) $(LIBS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX) clean

fclean	:	clean
		rm -f $(NAME) $(LIBFT)
		$(MAKE) -C $(LIBFT_DIR) fclean

re	:	fclean all

run : $(NAME)
	./$(NAME) test_maps/$(FILE).fdf

.PHONY: all clean fclean re run
-include DEPS
