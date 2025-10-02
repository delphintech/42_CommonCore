/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:09:06 by dabouab           #+#    #+#             */
/*   Updated: 2024/07/04 15:32:14 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_clear(char *msg, char **tab)
{
	int	l;

	if (tab)
	{
		l = 0;
		while (tab[l])
		{
			free(tab[l]);
			l++;
		}
		free(tab);
	}
	if (msg)
	{
		l = 0;
		while (msg[l])
			l++;
		write(STDERR_FILENO, msg, l);
		exit(EXIT_FAILURE);
	}
}

char	**check_args(int ac, char **av, char **env)
{
	char	**paths;

	paths = get_paths(env);
	if (ac < 5)
		exit_clear("Too few arguments\n", paths);
	if (ac > 5)
		exit_clear("Too many arguments\n", paths);
	if (!paths)
		exit_clear("No environnement paths found\n", NULL);
	if (access(av[1], F_OK & R_OK) == -1)
	{
		perror(av[1]);
		exit_clear(NULL, paths);
		exit(EXIT_FAILURE);
	}
	return (paths);
}

char	**get_paths(char **env)
{
	int		i;
	char	*swap;
	char	**tab;

	i = 0;
	tab = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			tab = ft_split(env[i], ':');
			break ;
		}
		i++;
	}
	swap = ft_strdup(&tab[0][5]);
	free(tab[0]);
	tab[0] = swap;
	return (tab);
}

void	exec_cmd(char **cmd, char **paths, char **env)
{
	int		i;
	char	*temp;
	char	*exec_path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		exec_path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		exec_path = NULL;
		i++;
	}
	if (!exec_path || execve(exec_path, cmd, env) == -1)
	{
		if (exec_path)
			free(exec_path);
		exit_clear(NULL, cmd);
		exit_clear("Command not found\n", paths);
	}
	exit_clear(NULL, cmd);
	free(exec_path);
}
