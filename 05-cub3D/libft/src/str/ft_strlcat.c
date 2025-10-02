/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:33:26 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:35 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	tot_len;

	i = 0;
	j = 0;
	if ((!dst || !src) && !len)
		return (0);
	while (dst[i] && i < len)
		i++;
	if (i < len)
		tot_len = i + ft_strlen(src);
	else
		return (len + ft_strlen(src));
	while (src[j] && (i + j + 1) < len)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (tot_len);
}
