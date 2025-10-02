/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:05:53 by magahat           #+#    #+#             */
/*   Updated: 2024/09/13 09:31:23 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_intlen_base(long n, int len_base)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len = 1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / len_base;
		len++;
	}
	return (len);
}
