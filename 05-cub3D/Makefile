#################### EXEC ####################

ARG = assets/maps/b1.cub

#################### SETUP ####################

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
MLX_FLAG	=  -lmlx -L$(MLX_DIR) -lXext -lX11 -lm -lz

BLUE 		= \e[1;96m
L_RED 		= \e[31m
B_RED 		= \e[1;31m
RESET 		= \e[0m
NOPRINT		= --no-print-directory

#################### INCLUDES ####################

INCLD			= -Iincludes -Iminilibx-linux

LIBFT 			= .libft
LIBFT_DIR 		= libft/
LIBFT_A			= ./libft/libft.a

$(LIBFT) :
	@$(MAKE) $(NOPRINT) -C $(LIBFT_DIR)
	@touch $@

MLX				= .mlx
MLX_DIR			= minilibx-linux/
MLX_A			= ./minilibx-linux/libmlx.a

$(MLX) :
	@$(MAKE) $(NOPRINT) -C $(MLX_DIR)
	@touch $@

#################### PATH ####################

INCL_PATH		= includes/
SRC_PATH		= src/
SRC_PATH_PARS	= parsing/
SRC_PATH_RAY	= image/
SRC_PATH_GAME	= game/
SRC_PATH_BONUS	= bonus/

#################### SRC & OBJ ####################

SRC			= main.c
SRC_PARS	= parsing.c parsing_utils.c checks.c tabs_utils.c
SRC_GAME	= game.c movement.c orientation.c exit_game.c
SRC_RAY		= visual.c textures.c raycasting.c draw_map.c
SRC_BONUS	= minimap.c door.c draw_minimap.c

SRCS_PARS	= $(addprefix $(SRC_PATH_PARS), $(SRC_PARS))
SRCS_GAME	= $(addprefix $(SRC_PATH_GAME), $(SRC_GAME))
SRCS_RAY	= $(addprefix $(SRC_PATH_RAY), $(SRC_RAY))
SRCS_BONUS	= $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS))
SRCS		=	$(addprefix $(SRC_PATH), $(SRC)) \
				$(addprefix $(SRC_PATH), $(SRCS_PARS)) \
				$(addprefix $(SRC_PATH), $(SRCS_GAME)) \
				$(addprefix $(SRC_PATH), $(SRCS_RAY)) \
				$(addprefix $(SRC_PATH), $(SRCS_BONUS))

OBJS 		= $(SRCS:.c=.o)

#################### RULES ####################

all	: $(NAME)

clean:
		@$(MAKE) $(NOPRINT) -C $(LIBFT_DIR) clean
		@$(MAKE) $(NOPRINT) -C $(MLX_DIR) clean
		@printf "${L_RED}Deleting $(NAME) objects ......"
		@rm -f $(OBJS) $(LIBFT) $(MLX)
		@printf " ✅${RESET}\n"

fclean: clean
		@$(MAKE) $(NOPRINT) -C $(LIBFT_DIR) fclean
		@printf "${L_RED}Deleting $(NAME) executable ............"
		@rm -f $(NAME)
		@printf " ✅${RESET}\n"

re: fclean all

run : $(NAME)
	./$(NAME) $(ARG)
	
#################### COMPILATION ####################

# MANDATORY
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(OBJS) $(MLX_FLAG) $(LIBFT_A) $(MLX_A) -o $(NAME)
	@printf "\n"
	@printf "${BLUE} .----------------.  .----------------.  .----------------.  .----------------.  .----------------. ${RESET}\n"
	@printf "${BLUE}| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |${RESET}\n"
	@printf "${BLUE}| |     ______   | || | _____  _____ | || |   ______     | || |    ______    | || |  ________    | |${RESET}\n"
	@printf "${BLUE}| |   .  ___  |  | || ||_   _||_   _|| || |  |_   _ \    | || |   / ____  .  | || | |_   ___  .  | |${RESET}\n"
	@printf "${BLUE}| |  / .    \_|  | || |  | |    | |  | || |    | |_) |   | || |       __) |  | || |   | |    . \ | |${RESET}\n"
	@printf "${BLUE}| |  | |         | || |  | |    | |  | || |    |  __ .   | || |   _  |__  .  | || |   | |    | | | |${RESET}\n"
	@printf "${BLUE}| |  \  .___. \  | || |   \  --  /   | || |   _| |__) |  | || |  | \____) |  | || |  _| |___.  / | |${RESET}\n"
	@printf "${BLUE}| |    ._____.   | || |     .__.     | || |  |_______/   | || |   \______.   | || | |________.   | |${RESET}\n"
	@printf "${BLUE}| |              | || |              | || |              | || |              | || |              | |${RESET}\n"
	@printf "${BLUE}|  --------------  ||  --------------  ||  --------------  ||  --------------  ||  --------------  |${RESET}\n"
	@printf "${BLUE}  ----------------    ----------------    ----------------    ----------------    ----------------  ${RESET}\n"
	@printf "\n"

#################### DIVERS ####################

copy_minilibx:
		@cp -r ~/Downloads/minilibx-linux minilibx-linux

.PHONY: all clean fclean re