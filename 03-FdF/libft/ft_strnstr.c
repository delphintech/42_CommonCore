/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:12:57 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/24 14:46:24 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static char	*ft_find(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*found;

	i = 0;
	j = 0;
	while (big[i] && i < len && little[j])
	{
		if (big[i] == little[j])
		{
			if (j == 0)
				found = (char *)&big[i];
			j++;
		}
		else
		{
			found = 0;
			i -= j;
			j = 0;
		}
		i++;
	}
	if (j == ft_strlen(little))
		return (found);
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*found;

	found = (char *)big;
	if (*little == '\0')
		return (found);
	return (ft_find(big, little, len));
}
