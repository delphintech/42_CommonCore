/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:50:36 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 13:55:32 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	initialize(t_params *params, int argc, char **argv, char **envp)
{
	if (argc != 1)
		exit_clear("This program does not take any arguments !!",
			EXIT_FAILURE, NULL, NULL);
	(void)argv;
	params->env = dup_env(envp);
	params->envp = envp;
	params->err_code = 0;
	params->cmd_input = NULL;
	g_sig = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_params	params;
	t_parsing	*parsing;

	initialize(&params, argc, argv, envp);
	while (1)
	{
		signal(SIGINT, &handler);
		signal(SIGQUIT, SIG_IGN);
		params.input = readline("\001\e[1;35m\002 Minishell>\001\e[0m\002 ");
		if (!params.input)
			exit_clear("exit", params.err_code, &params, NULL);
		add_history(params.input);
		parsing = manage_parsing(&params);
		if (parsing)
		{
			process(&params, &parsing);
			clear_parsing_list(parsing);
		}
	}
	exit_clear("", EXIT_SUCCESS, &params, parsing);
}
