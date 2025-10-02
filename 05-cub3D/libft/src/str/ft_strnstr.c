/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:24:30 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:50 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_str_cmp(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(little);
	while (big[i] == little[i] && i < len && big[i])
		i++;
	if (i == l)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	if (!len)
		return (NULL);
	i = 0;
	while (big[i] && i <= len - 1)
	{
		if (big[i] == little[0] && ft_str_cmp(&big[i], little, len - i) == 1)
			return (&((char *)big)[i]);
		i++;
	}
	return (NULL);
}
