/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:32:47 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/20 11:43:42 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	table_size(char	**tab)
{
	int	i;

	if (!tab || !*tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**tab_add(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	if (!str)
		return (tab);
	new_tab = malloc((table_size(tab) + 2) * sizeof(char *));
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	new_tab[i] = ft_strdup(str);
	i++;
	new_tab[i] = NULL;
	return (new_tab);
}

void	clear_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	clear_tab_line(char **tab, char *line)
{
	if (tab)
		clear_tab(tab);
	if (line)
		free(line);
}

int	check_tab_char(char **tab, int size, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (i < size && tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (ft_charcmp(tab[i][j], set) == 0)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}
