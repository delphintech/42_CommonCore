/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:44:00 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:07 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *dst, int c, size_t len)
{
	void	*tmp;

	tmp = dst;
	while (len--)
		*(unsigned char *)dst++ = (unsigned char)c;
	return (tmp);
}
