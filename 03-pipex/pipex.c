/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:25:29 by dabouab           #+#    #+#             */
/*   Updated: 2024/07/04 15:43:54 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_child(int pfd[2], char **av, char **paths, char **env)
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile < 0)
		exit_clear("No such file or directory", paths);
	close(pfd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	exec_cmd(ft_split(av[2], ' '), paths, env);
	close(pfd[1]);
	close(infile);
}

int	main(int ac, char **av, char **env)
{
	int		outfile;
	int		pfd[2];
	int		pid;
	char	**paths;

	paths = check_args(ac, av, env);
	if (pipe(pfd) == -1)
		exit_clear("Pipe failed\n", paths);
	pid = fork();
	if (pid < 0)
		exit_clear("Fork failed\n", paths);
	if (pid == 0)
		run_child(pfd, av, paths, env);
	waitpid(pid, NULL, 0);
	outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (outfile < 0)
		exit_clear("No such file or directory", paths);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(ft_split(av[3], ' '), paths, env);
	close(pfd[0]);
	close(outfile);
	exit_clear(NULL, paths);
	return (EXIT_SUCCESS);
}
