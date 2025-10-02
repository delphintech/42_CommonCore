/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:52 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 17:54:11 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// *type_redir_in; // 0: file_name, 1: delimiter
int	get_infile(t_params *params, t_parsing *cmd_data)
{
	int	i;

	i = 0;
	while (i < cmd_data->nb_redir_in)
	{
		if (cmd_data->type_redir_in[i] == 0)
		{
			if (access(cmd_data->redir_in[i], F_OK) == -1)
				return (ft_error(params, 1, "No such file or directory",
						cmd_data->redir_in[i]), -1);
			if (access(cmd_data->redir_in[i], R_OK) == -1)
				return (ft_error(params, 1, "Permission denied",
						cmd_data->redir_in[i]), -1);
		}
		i++;
	}
	if (cmd_data->nb_redir_in > 0)
		return (1);
	return (0);
}

// 	*type_redir_out; // 0: > (trunc), 1: >> (append)
int	get_outfile(t_params *params, t_parsing *cmd_data, int keep)
{
	int	i;
	int	fd;

	fd = 0;
	i = -1;
	while (++i < cmd_data->nb_redir_out)
	{
		if (cmd_data->type_redir_out[i] == 0)
			fd = open(cmd_data->redir_out[i],
					O_WRONLY | O_CREAT | O_TRUNC, 00644);
		else
			fd = open(cmd_data->redir_out[i],
					O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (fd < 0)
			return (ft_error(params, 1, "Permission denied",
					cmd_data->redir_out[i]), -1);
		if (keep == FALSE)
			close(fd);
		else if (i < cmd_data->nb_redir_out - 1)
			close(fd);
		if (!ft_strncmp(cmd_data->redir_out[i], "/dev/full", 10))
			return (close(fd), ft_error(params, 1,
					"write error: No space left on device", cmd_data->cmd), -1);
	}
	return (fd);
}

char	*get_path(t_params *params, t_parsing *cmd_data)
{
	int		i;
	char	*cmd_path;
	char	**paths;

	if (!cmd_data->cmd)
		return ("");
	if (access(cmd_data->cmd, X_OK) == 0)
		return (ft_strdup(cmd_data->cmd));
	cmd_path = getcwd(NULL, 0);
	cmd_path = str_join_replace(cmd_path, ft_strdup(cmd_data->cmd));
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	paths = ft_split(get_env_value(params->env, "PATH"), ':');
	i = 0;
	while (paths && paths[i])
	{
		cmd_path = ft_strjoin(paths[i++], "/");
		cmd_path = str_join_replace(cmd_path, ft_strdup(cmd_data->cmd));
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	free_tab_char(paths);
	return (ft_error(params, 127, "command not found", cmd_data->cmd), NULL);
}

char	**path_in_args(t_parsing	*cmd_data, char	*path)
{
	int		i;
	char	**tab;

	tab = malloc((cmd_data->nb_arg + 2) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = path;
	i = 0;
	while (cmd_data->arg[i])
	{
		tab[i + 1] = cmd_data->arg[i];
		i++;
	}
	tab[i + 1] = NULL;
	free(cmd_data->arg);
	return (tab);
}
