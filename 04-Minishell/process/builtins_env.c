/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:03 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/11 11:01:55 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_name_valid(char *name)
{
	int	check;
	int	i;

	check = TRUE;
	if (!name || !*name)
		return (FALSE);
	i = 0;
	if (ft_isdigit(name[0]) > 0)
		return (FALSE);
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			check = FALSE;
		i++;
	}
	return (check);
}

int	ft_export_var(t_params *params, char *name, char *value)
{
	t_var	*temp;

	temp = find_var(params->env, name);
	if (!temp)
	{
		if (is_var_name_valid(name))
		{
			temp = ft_new_var(name, value);
			var_add_back(params->env, temp);
		}
		else
		{
			if (!name)
				name = ft_strjoin("=", value);
			ft_error(params, 1, "Identifier not valid", name);
			return (free(name), EXIT_FAILURE);
		}
	}
	else
	{
		free(temp->value);
		temp->value = value;
		free(name);
	}
	return (EXIT_SUCCESS);
}

// export with no options
void	ft_export(t_params *params, t_parsing *cmd_data)
{
	int		i;
	char	*name;
	char	*value;

	if (cmd_data->nb_arg == 0
		|| (cmd_data->nb_arg == 1 && ft_strncmp(cmd_data->arg[0], "", 1) == 0))
		return (ft_env(params, cmd_data));
	i = 0;
	while (cmd_data->arg[i])
	{
		name = ft_strbchr(cmd_data->arg[i], '=');
		value = ft_strdup(ft_strchr(cmd_data->arg[i], '='));
		name = remove_index(name, ft_strlen(name) - 1, '=');
		value = remove_index(value, 0, '=');
		if (ft_export_var(params, name, value) == EXIT_FAILURE)
		{
			if (value)
				free(value);
		}
		i++;
	}
	params->err_code = 0;
}

// unset with no options
void	ft_unset(t_params *params, t_parsing *cmd_data)
{
	int		i;
	t_var	*var;

	i = 0;
	if (cmd_data->nb_arg == 0)
	{
		params->err_code = 0;
		return ;
	}
	while (cmd_data->arg[i])
	{
		var = find_var(params->env, cmd_data->arg[i]);
		del_var(params->env, var);
		i++;
	}
	params->err_code = 0;
}

// env with no options or arguments
void	ft_env(t_params *params, t_parsing *cmd_data)
{
	t_var	*temp;

	if (ft_strncmp(cmd_data->cmd, "env", 4) == 0 && cmd_data->arg)
		return ((void)ft_error(params, 1, "too many arguments", "env"));
	temp = *params->env;
	while (temp)
	{
		if (ft_strncmp(cmd_data->cmd, "export", 7) == 0)
			ft_printf_fd(1, "export ");
		if (temp->value && ft_strncmp(cmd_data->cmd, "export", 7) != 0)
			ft_printf_fd(1, "%s=%s\n", temp->name, temp->value);
		else if (temp->value)
			ft_printf_fd(1, "%s=\"%s\"\n", temp->name, temp->value);
		else if (ft_strncmp(cmd_data->cmd, "export", 7) == 0)
			ft_printf_fd(1, "%s\n", temp->name);
		temp = temp->next;
	}
	params->err_code = 0;
}
