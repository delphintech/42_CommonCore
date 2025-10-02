/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:26:20 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:01:57 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_zero(void *str, size_t n)
{
	while (n--)
		*(unsigned char *)str++ = 0;
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*str;

	if (number > INT_MAX || size > INT_MAX || size * number > INT_MAX)
		return (NULL);
	str = malloc(number * size);
	if (!str)
		return (NULL);
	ft_zero(str, number * size);
	return (str);
}
