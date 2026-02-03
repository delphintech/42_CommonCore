/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:11:48 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/24 14:46:41 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	sdest;

	sdest = ft_strlen(dst);
	if (siz == 0)
		return (ft_strlen(src) + siz);
	i = 0;
	while (dst[i] && i < siz - 1)
		i++;
	j = 0;
	while (src[j] && i < siz - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (siz > sdest)
		dst[i] = '\0';
	if (siz < sdest)
		return (ft_strlen(src) + siz);
	else
		return (ft_strlen(src) + sdest);
}
