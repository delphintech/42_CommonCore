/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:49:18 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 17:39:37 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*infile_path(t_params *params, t_parsing *cmd, int fd_in, int pfd[2])
{
	char	*path;

	if (get_infile(params, cmd) < 0)
	{
		close(pfd[1]);
		exit_clear("", params->err_code, params, cmd);
	}
	else if (get_infile(params, cmd) > 0)
	{
		close(fd_in);
		fd_in = open(cmd->redir_in[cmd->nb_redir_in - 1], O_RDONLY);
	}
	dup2(fd_in, STDIN_FILENO);
	if (fd_in > 0)
		close(fd_in);
	if (!is_builtins(cmd))
	{
		path = get_path(params, cmd);
		return (path);
	}
	return (NULL);
}

int	outfile(t_params *params, t_parsing *cmd, int pfd[2])
{
	int	fd_out;

	fd_out = get_outfile(params, cmd, TRUE);
	if (fd_out < 0)
	{
		close(pfd[1]);
		exit_clear("", params->err_code, params, cmd);
	}
	else if (fd_out > 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (cmd->next)
		dup2(pfd[1], STDOUT_FILENO);
	return (fd_out);
}

void	children(t_params *params, t_parsing *cmd, int fd_in, int pfd[2])
{
	int		fd_out;
	char	*path;

	signal(SIGQUIT, &child_handler);
	close(pfd[0]);
	if (get_outfile(params, cmd, FALSE) == -1)
		return ;
	path = infile_path(params, cmd, fd_in, pfd);
	if (path && cmd->nb_arg > 0)
		cmd->arg = path_in_args(cmd, path);
	fd_out = outfile(params, cmd, pfd);
	if (exec_builtins(params, cmd))
		return ((void)close(fd_out));
	close(pfd[1]);
	if (path && execve(path, cmd->arg, params->envp) == -1 && cmd->cmd)
	{
		free(path);
		ft_error(params, 126, "Command not found", cmd->cmd);
		close(pfd[1]);
		close(fd_in);
		return ((void)close(fd_out));
	}
	close(fd_out);
}

int	make_child(t_params *params, t_parsing *cmd_data, int fd_in, int stdin_copy)
{
	int		pfd[2];
	pid_t	pid;

	if (pipe(pfd) == -1)
		return (ft_error(params, 32, "Pipe failed", cmd_data->cmd), -1);
	pid = fork();
	if (pid < 0)
		return (ft_error(params, 10, "Process failed", cmd_data->cmd), -1);
	if (pid == 0)
	{
		close(stdin_copy);
		children(params, cmd_data, fd_in, pfd);
		close(fd_in);
		close(pfd[1]);
		exit_clear("", params->err_code, params, cmd_data);
	}
	signal(SIGINT, &child_handler);
	signal(SIGQUIT, &child_handler);
	close(fd_in);
	close(pfd[1]);
	return (pfd[0]);
}

void	process(t_params *params, t_parsing **cmd_list)
{
	int			fd_in;
	int			stdin_copy;
	t_parsing	*cmd_data;

	check_heredoc(cmd_list);
	stdin_copy = dup(STDIN_FILENO);
	fd_in = STDIN_FILENO;
	cmd_data = *cmd_list;
	while (cmd_data)
	{
		if (cmd_data == *cmd_list && !cmd_data->next)
			env_builtins(params, cmd_data, stdin_copy);
		fd_in = make_child(params, cmd_data, fd_in, stdin_copy);
		if (fd_in < 0)
			break ;
		cmd_data = cmd_data->next;
	}
	wait_children(params);
	g_sig = 0;
	close(fd_in);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	if (access(".temp", F_OK) == 0)
		unlink(".temp");
}
