/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:45:05 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:56 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	ft_str_size(const char *s, unsigned int start, size_t len)
{
	if (ft_strlen(s) < start)
		return (0);
	else if (len > ft_strlen(s) - start)
		return (ft_strlen(s) - start);
	else
		return (len);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	int		j;
	size_t	size;

	size = ft_str_size(s, start, len);
	substr = malloc(sizeof(char) * size + 1);
	if (!substr)
		return (NULL);
	j = 0;
	while (size-- && s[start + j])
	{
		substr[j] = s[start + j];
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
