/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:57:04 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 10:55:23 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>

# define TRUE	1
# define FALSE	0

extern int	g_sig;

typedef struct s_var
{
	char				*name;
	char				*value;
	struct s_var		*prev;
	struct s_var		*next;
}	t_var;

typedef struct s_params
{
	char				*input;
	t_var				**env;
	char				**envp;
	int					err_code;
	int					nb_cmd;
	char				**cmd_input;
	HIST_ENTRY			**input_history;
}	t_params;

typedef struct s_parsing
{
	char				*input;
	char				*cmd;
	char				**arg;
	int					nb_arg;
	int					nb_redir_in;
	int					nb_redir_out;
	char				**redir_in;
	int					*type_redir_in;
	char				**redir_out;
	int					*type_redir_out;
	struct s_parsing	*next;
	struct s_parsing	*prev;
}	t_parsing;

#endif
