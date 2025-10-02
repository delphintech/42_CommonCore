/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:44:29 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:15 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_int_len(int n)
{
	unsigned int	x;
	int				len;

	len = 0;
	if (n < 0)
	{
		x = -n;
		len = 1;
	}
	else
		x = n;
	if (n == 0)
		return (1);
	while (x > 0 && len < 11)
	{
		x = x / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	x;
	int				len;
	char			*str;

	len = ft_int_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		x = -n;
		str[0] = '-';
	}
	else
		x = n;
	str[len] = '\0';
	while (len-- > 1)
	{
		str[len] = '0' + (x % 10);
		x /= 10;
	}
	if (n >= 0)
		str[0] = '0' + (x % 10);
	return (str);
}
