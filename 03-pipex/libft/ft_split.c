/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:24:00 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/27 10:40:26 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	ft_free(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_count_word(const char *str, char c)
{
	int	i;
	int	l;
	int	count;

	l = ft_strlen(str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] != c)
			|| (str[i] == c && str[i - 1] != c && i != l - 1))
			count += 1;
		i++;
	}
	return (count);
}

static char	*ft_fillstr(char *tab, char const *s, char c, int i)
{
	int	j;
	int	l;

	j = i;
	l = 0;
	while (s[j] && s[j] != c)
	{
		j++;
		l++;
	}
	tab = ft_substr(s, i, l);
	return (tab);
}

static int	ft_filltab(char **tab, char const *s, char c)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			tab[j] = ft_fillstr(tab[j], s, c, i);
			if (!tab[j])
			{
				ft_free(tab, j);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		l;
	char	**tab;

	if (!c)
		c = '\0';
	if (!s)
		return (NULL);
	l = ft_count_word(s, c);
	tab = (char **)malloc((l + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	j = ft_filltab(tab, s, c);
	if (j == -1)
		return (NULL);
	tab[j] = NULL;
	return (tab);
}
