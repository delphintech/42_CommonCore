/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:45 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/09 17:30:31 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_builtins(t_params *params, t_parsing *cmd_data, int stdin_copy)
{
	if (ft_strncmp(cmd_data->cmd, "cd", 3) == 0)
		return (ft_cd(params, cmd_data), FALSE);
	if (ft_strncmp(cmd_data->cmd, "export", 7) == 0 && cmd_data->arg)
		return (ft_export(params, cmd_data), FALSE);
	if (ft_strncmp(cmd_data->cmd, "unset", 6) == 0)
		return (ft_unset(params, cmd_data), FALSE);
	if (ft_strncmp(cmd_data->cmd, "exit", 5) == 0)
		return (ft_exit(params, cmd_data, stdin_copy), TRUE);
	return (FALSE);
}

int	is_builtins(t_parsing *cmd_data)
{
	if (ft_strncmp(cmd_data->cmd, "echo", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "export", 7) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "unset", 6) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "exit", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "$?", 3) == 0)
		return (TRUE);
	return (FALSE);
}

int	exec_builtins(t_params *params, t_parsing *cmd_data)
{
	if (ft_strncmp(cmd_data->cmd, "echo", 5) == 0)
		return (ft_echo(params, cmd_data), TRUE);
	if (ft_strncmp(cmd_data->cmd, "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "pwd", 4) == 0)
		return (ft_pwd(params), TRUE);
	if (ft_strncmp(cmd_data->cmd, "export", 7) == 0 && !cmd_data->arg)
		return (ft_export(params, cmd_data), TRUE);
	if (ft_strncmp(cmd_data->cmd, "export", 7) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "unset", 6) == 0)
		return (TRUE);
	if (ft_strncmp(cmd_data->cmd, "env", 4) == 0)
		return (ft_env(params, cmd_data), TRUE);
	if (ft_strncmp(cmd_data->cmd, "exit", 5) == 0 && cmd_data->nb_arg < 2)
		return (ft_exit(params, cmd_data, -1), TRUE);
	if (ft_strncmp(cmd_data->cmd, "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}

int	is_n_option(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	i = 0;
	if (str[i++] != '-')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
