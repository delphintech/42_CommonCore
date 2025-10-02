/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:49:57 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/11 10:58:24 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// echo with option -n
void	ft_echo(t_params *params, t_parsing *cmd_data)
{
	int	i;
	int	new_line;

	if (!cmd_data->arg)
		return ((void)ft_printf_fd(1, "\n"));
	new_line = TRUE;
	i = 0;
	while (cmd_data->arg[i] && is_n_option(cmd_data->arg[i]))
	{
		new_line = FALSE;
		i++;
	}
	while (cmd_data->arg[i])
	{
		ft_printf_fd(1, "%s", cmd_data->arg[i]);
		if (i < cmd_data->nb_arg - 1 && cmd_data->nb_arg > 1)
			ft_printf_fd(1, " ");
		i++;
	}
	if (new_line)
		ft_printf_fd(1, "\n");
	params->err_code = 0;
}

void	ft_cd_exec(t_params *params, t_parsing *cmd_data, char *str)
{
	if (!str && cmd_data->nb_arg > 0)
	{
		if (cmd_data->arg[0][0] == '/')
			str = ft_strjoin(".", cmd_data->arg[0]);
		else if (cmd_data->arg[0][0] == '~')
			str = ft_strjoin(getenv("HOME"), &cmd_data->arg[0][1]);
		else
			str = ft_strdup(cmd_data->arg[0]);
	}
	ft_export_var(params, ft_strdup("OLDPWD"), getcwd(NULL, 0));
	if (chdir(str) == -1)
		return (free(str), (void)ft_error(params, 1,
				"No such file or directory", "cd"));
	free(str);
	params->err_code = 0;
}

// cd with only a relative or absolute path
void	ft_cd(t_params *params, t_parsing *cmd_data)
{
	char	*str;

	str = NULL;
	if (cmd_data->nb_arg == 0)
	{
		str = ft_strdup(get_env_value(params->env, "HOME"));
		if (!str)
			return ((void)ft_error(params, 1, "HOME not set", "cd"));
	}
	else if (cmd_data->nb_arg > 1)
		return ((void)ft_error(params, 1, "too many arguments", "cd"));
	else if (ft_strncmp(cmd_data->arg[0], "", 2) == 0)
	{
		str = ft_strdup(get_env_value(params->env, "HOME"));
		if (!str)
			return ((void)ft_error(params, 1, "HOME not set", "cd"));
	}
	else if (cmd_data->arg[0][0] == '-')
	{
		str = ft_strdup(get_env_value(params->env, "OLDPWD"));
		if (!str)
			return ((void)ft_error(params, 1, "OLDPWD not set", "cd"));
		ft_printf_fd(1, "%s\n", str);
	}
	ft_cd_exec(params, cmd_data, str);
}

// pwd with no options
void	ft_pwd(t_params *params)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_error(params, 1, "error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory",
			"pwd");
		return ;
	}
	ft_printf_fd(1, "%s\n", path);
	params->err_code = 0;
	free(path);
}

// exit with no options
void	ft_exit(t_params *params, t_parsing *cmd_list, int stdin_copy)
{
	long long	nb;

	if (stdin_copy != -1)
		ft_printf_fd(1, "exit\n");
	if (cmd_list->arg && ft_is_valid_num(cmd_list->arg[0]) == FALSE)
	{
		close(stdin_copy);
		ft_error(params, 2, "numeric argument required", "exit");
		exit_clear("", 2, params, cmd_list);
	}
	if (cmd_list->arg && cmd_list->arg[1] && params->err_code == 0)
		return ((void)ft_error(params, 1, "too many arguments", "exit"));
	else if (cmd_list->arg && cmd_list->arg[1] && params->err_code != 0)
		return ((void)ft_printf_fd(2, "minishell: exit: too many arguments\n"));
	close(stdin_copy);
	if (!cmd_list->arg)
		exit_clear("", 0, params, cmd_list);
	nb = ft_atoi_long(cmd_list->arg[0]);
	if (nb < 0 || nb > 255)
		exit_clear("", 255, params, cmd_list);
	exit_clear("", nb, params, cmd_list);
}
