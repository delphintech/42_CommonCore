CC = cc

CFLAGS += -Werror -Wall -Wextra -g3

LIBFT = .libft
LIBFT_DIR = libft/

NAME = minishell

SRCS += main.c \
	process/builtins_env.c \
	process/builtins_exec.c \
	process/builtins.c \
	process/checks.c \
	process/env.c \
	process/heredoc.c \
	process/process.c \
	process/struct_var.c

SRCS += parsing/check_input.c \
	parsing/expansion.c \
	parsing/init_struct_parsing.c \
	parsing/parsing.c \
	parsing/cmd_and_arg.c \
	parsing/cmd_and_arg_utils.c \
	parsing/parsing_split.c \
	parsing/parsing_utils.c \
	parsing/redirections.c \
	parsing/redirections_utils.c \
	parsing/quotes.c \
	parsing/quotes_utils.c

SRCS += utils/function_utils.c \
	utils/program_utils.c \
	utils/utils_free.c \
	utils/utils_pour_tests.c

OBJS = $(SRCS:.c=.o)

PURPLE = \e[35m
L_RED = \e[31m
RESET = \e[0m

all	: $(NAME)

$(LIBFT) :
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@touch $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline
	@printf "\n${PURPLE}"
	@printf "  ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
	@printf "  ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
	@printf "  ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"
	@printf "  ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
	@printf "  ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
	@printf "  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
	@printf "\n${RESET}"

clean	:
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
		@printf "${L_RED}Deleting minishell objects ......"
		@rm -f $(OBJS) $(LIBFT)
		@printf " ✅${RESET}\n"

fclean	:	clean
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
		@printf "${L_RED}Deleting minishell executable ............"
		@rm -f $(NAME)
		@printf " ✅${RESET}\n"

re	:	fclean all

.PHONY: all clean fclean re

# ------- Pour le developpement --------

DBGFLAGS := -g3

debug :  $(SRCS) $(LIBFT)            ## Permet de debuger le code avec lldb
	$(CC) ${DBGFLAGS} -o $(NAME) $(SRCS) $(LIB) -L$(LIBFT_DIR) -lft -lreadline
	lldb ./$(NAME)

val :   $(SRCS) $(LIBFT)                    ## Lance le check valgrind
	$(CC) ${DBGFLAGS} -o $(NAME)  $(SRCS) $(LIB) -L$(LIBFT_DIR) -lft -lreadline
	ulimit -n 20 valgrind --tool=memcheck --leak-check=full --suppressions=.val.supp \
		--trace-children=yes --track-fds=all --show-leak-kinds=all \
		--track-origins=yes -s ./$(NAME) 
