/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:06:14 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/24 14:47:39 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	ft_fill(char *str, char const *s1, int start, int end)
{
	int		i;

	i = 0;
	while (start <= end && end != 0)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!set)
		return ((char *)s1);
	start = 0;
	while (s1[start] && ft_isset(s1[start], set) == 1)
		start++;
	end = ft_strlen(s1) - 1;
	while (end > 0 && ft_isset(s1[end], set) == 1)
		end--;
	if (end == 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc((end - start + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_fill(str, s1, start, end);
	return (str);
}
