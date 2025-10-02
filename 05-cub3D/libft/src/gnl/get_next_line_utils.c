/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:29:29 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/29 16:54:51 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t siz)
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

char	*ft_strljoin_gnl(char *s1, char *s2, size_t l)
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
