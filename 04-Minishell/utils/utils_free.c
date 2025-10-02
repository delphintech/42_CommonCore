/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:06:10 by magahat           #+#    #+#             */
/*   Updated: 2024/10/09 15:17:24 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*free_null(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

void	free_tab_char(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
	tab = NULL;
}

char	*str_join_replace(char *s1, char *s2)
{
	char	*dst;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	dst = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (dst);
}

void	clear_parsing_list(t_parsing *parsing)
{
	t_parsing	*temp;

	if (!parsing)
		return ;
	parsing = go_start_parsing(parsing);
	while (parsing)
	{
		temp = parsing->next;
		if (parsing->cmd)
			free(parsing->cmd);
		if (parsing->nb_arg)
			free_tab_char(parsing->arg);
		if (parsing->nb_redir_in > 0)
		{
			free_tab_char(parsing->redir_in);
			free(parsing->type_redir_in);
		}
		if (parsing->nb_redir_out > 0)
		{
			free_tab_char(parsing->redir_out);
			free(parsing->type_redir_out);
		}
		free(parsing);
		parsing = temp;
	}
}
