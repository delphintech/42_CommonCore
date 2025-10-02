/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:33:53 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/24 16:52:00 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static void	ft_fill(char *sub, char const *s, unsigned int i, size_t len)
{
	size_t	j;

	j = 0;
	while (s[i] && j < len)
	{
		sub[j] = s[i];
		i++;
		j++;
	}
	sub[j] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*sub;

	l = ft_strlen(s);
	if (start > l)
	{
		sub = (char *)malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (l - start >= len)
		sub = (char *)malloc((len + 1) * sizeof(char));
	else
		sub = (char *)malloc((l - start + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_fill(sub, s, start, len);
	return (sub);
}
