/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:57:26 by magahat           #+#    #+#             */
/*   Updated: 2024/09/21 18:48:36 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	correct_format_redir(char *input)
{
	if (ft_charcmp(input[0], "><") && ft_charcmp(input[1], "><")
		&& ft_charcmp(input[2], "><"))
		return (0);
	else if (input[0] == '>' && input[1] == '<')
		return (0);
	else if (ft_charcmp(input[0], "<>") && !ft_charcmp(input[1], "<>"))
		return (1);
	else if (ft_charcmp(input[0], "<>") && ft_charcmp(input[1], "<>"))
		return (2);
	return (1);
}

void	count_redirections(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->input[i])
	{
		if (parsing->input[i] == '<')
		{
			parsing->nb_redir_in++;
			i += correct_format_redir(&parsing->input[i]);
		}
		else if (parsing->input[i] == '>')
		{
			parsing->nb_redir_out++;
			i += correct_format_redir(&parsing->input[i]);
		}
		else if (is_quote(parsing->input[i]))
			i += go_end_quote(&parsing->input[i], parsing->input[i]);
		else
			i++;
	}
}

int	go_end_redir(char *input)
{
	int	i;
	int	l;

	i = 0;
	i += correct_format_redir(&input[i]);
	i += go_end_spaces(&input[i]);
	l = 0;
	while (input[i + l] && !ft_isspace(input[i + l])
		&& !ft_charcmp(input[i + l], "<>|"))
	{
		if (is_quote(input[i + l]))
			l += go_end_quote(&input[i + l], input[i + l]);
		else
			l++;
	}
	return (i + l);
}
