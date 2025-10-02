/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:19:14 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/11 11:05:51 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int signom)
{
	if (signom == SIGINT)
	{
		g_sig = signom;
		ft_printf_fd(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	child_handler(int signom)
{
	if (signom == SIGINT)
		ft_printf_fd(1, "\n");
	if (signom == SIGQUIT)
		ft_printf_fd(2, "Quit (core dumped)\n");
}

int	ft_error(t_params *params, int error_code, char *msg, char *cmd)
{
	if (error_code < 0 || error_code > 255)
		params->err_code = 255;
	else
		params->err_code = error_code;
	if (error_code != 0 && msg)
		printf("minishell: %s: %s\n", cmd, msg);
	return (error_code);
}

void	exit_clear(char *msg, int err_code,
		t_params *params, t_parsing *cmd_list)
{
	if (params)
	{
		rl_clear_history();
		clear_var_list(params->env);
	}
	if (cmd_list)
		clear_parsing_list(cmd_list);
	if (msg)
	{
		if (ft_strncmp(msg, "", 1) != 0)
			ft_printf_fd(2, "%s\n", msg);
		close(STDERR_FILENO);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		if (ft_strncmp(msg, "", 1) == 0)
			exit(err_code);
		exit(err_code);
	}
}

void	wait_children(t_params *params)
{
	int	err;

	while (params->nb_cmd)
	{
		waitpid(-1, &err, 0);
		params->nb_cmd--;
		if (WIFEXITED(err))
			params->err_code = WEXITSTATUS(err);
	}
}
