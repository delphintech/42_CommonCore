/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:08:10 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:01 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len)
	{
		if (((unsigned char *)b1)[i] != ((unsigned char *)b2)[i])
			return (((unsigned char *)b1)[i] - ((unsigned char *)b2)[i]);
		i++;
	}
	return (0);
}
