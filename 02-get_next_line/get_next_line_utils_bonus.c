/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:58:08 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/30 12:03:03 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

t_rest	*ft_lstnew(int fd)
{
	t_rest	*new;

	new = (t_rest *)malloc(sizeof(t_rest));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->rest[0] = '\0';
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_rest **lst, t_rest *new)
{
	t_rest	*last;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz == 0 && dst)
	{
		dst[0] = '\0';
		return (0);
	}
	while (src[i] && i < siz - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strljoin(char *s1, char *s2, size_t l)
{
	size_t		i;
	size_t		j;
	char		*str;

	str = (char *)malloc((ft_strlen(s1) + l) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < l - 1)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}
