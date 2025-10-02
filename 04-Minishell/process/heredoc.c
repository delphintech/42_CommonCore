/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:59 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 18:09:52 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_heredoc_input(char *limiter)
{
	char	*buf;
	int		tmp;
	int		len;

	len = ft_strlen(limiter);
	tmp = open(".temp", O_CREAT | O_TRUNC | O_WRONLY, 00744);
	if (tmp < 0)
		return (EXIT_FAILURE);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			ft_printf_fd(2, "warning: here-document delimited "
				"by end-of-file (wanted '%s')\n", limiter);
		if (g_sig == SIGINT || !buf)
			break ;
		if (!ft_strncmp(buf, limiter, len))
			if (buf[len] == '\n' || buf[len] == '\0')
				break ;
		ft_putendl_fd(buf, tmp);
		free(buf);
	}
	free(buf);
	close(tmp);
	return (EXIT_SUCCESS);
}

void	check_heredoc(t_parsing **cmd_list)
{
	t_parsing	*cmd;
	int			i;

	g_sig = 0;
	cmd = *cmd_list;
	while (cmd && g_sig != SIGINT)
	{
		if (cmd->nb_redir_in > 0)
		{
			i = 0;
			while (cmd->redir_in[i] && g_sig != SIGINT)
			{
				if (cmd->type_redir_in[i] == 1)
				{
					get_heredoc_input(cmd->redir_in[i]);
					free(cmd->redir_in[i]);
					cmd->redir_in[i] = ft_strdup(".temp");
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
	g_sig = 0;
}
