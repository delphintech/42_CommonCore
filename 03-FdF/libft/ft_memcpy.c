/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:07:20 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/24 14:13:00 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst;
	char	*s;

	if (!dest && !src)
		return (NULL);
	i = 0;
	s = (char *)src;
	dst = (char *)dest;
	while (i < n)
	{
		dst[i] = s[i];
		i++;
	}
	dest = dst;
	return (dest);
}
