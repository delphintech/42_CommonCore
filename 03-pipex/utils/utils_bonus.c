/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:06:22 by dabouab           #+#    #+#             */
/*   Updated: 2024/07/04 15:45:21 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	**check_args_bonus(int ac, char **av, char **env)
{
	char	**paths;

	paths = get_paths(env);
	if (ac < 5)
		exit_clear("Too few arguments\n", paths);
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

int	make_child(char *cmd, int fd_in, char **paths, char **env)
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
		exit_clear("Pipe failed\n", paths);
	pid = fork();
	if (pid < 0)
		exit_clear("Fork failed\n", paths);
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		exec_cmd(ft_split(cmd, ' '), paths, env);
		close(fd_in);
		close(pfd[1]);
	}
	close(pfd[1]);
	return (pfd[0]);
}

void	run_commands(int ac, char **av, char **paths, char **env)
{
	int		i;
	int		outfile;
	int		pfd_in;

	i = 2;
	while (i < ac - 2)
	{
		if (i == 2)
		{
			pfd_in = open(av[1], O_RDONLY, 0777);
			if (pfd_in < 0)
				exit_clear("No such file or directory", paths);
		}
		pfd_in = make_child(av[i], pfd_in, paths, env);
		i++;
	}
	wait(NULL);
	outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (outfile < 0)
		exit_clear("No such file or directory", paths);
	dup2(pfd_in, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(ft_split(av[i], ' '), paths, env);
	close(pfd_in);
	close(outfile);
}
