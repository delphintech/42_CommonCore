/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:26:03 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:54 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_setcmp(char c, char *set)
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

static int	ft_strlen_len(const char *str, char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0 && ft_setcmp(str[i], (char *)set))
		i--;
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*dst;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen_len(s1, (char *)set);
	while (s1[i] && ft_setcmp(s1[i], (char *)set))
		i++;
	if (len < i)
		dst = malloc(sizeof(char) * 1);
	else
		dst = malloc(sizeof(char) * len - i + 2);
	if (!dst)
		return (NULL);
	while (s1[i] && i <= len)
	{
		dst[j] = s1[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
