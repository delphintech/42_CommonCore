/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:21:41 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/05 13:07:50 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../ft_printf.h"

static char	*ft_itoa_malloc(long n, long p)
{
	int		size;
	char	*str;

	size = 1;
	while (p > 0)
	{
		size += 1;
		p = p / 10;
	}
	if (n < 0)
		str = (char *)malloc((size + 1) * sizeof(char));
	else
		str = (char *)malloc((size) * sizeof(char));
	return (str);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static long	ft_poweroftens(long n)
{
	long	p;

	if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	p = 1;
	while (p <= n)
	{
		p *= 10;
	}
	return (p / 10);
}

static void	ft_fill(char *str, int i, long n, long p)
{
	while (p > 0)
	{
		str[i] = n / p + '0';
		n = n % p;
		p = p / 10;
		i++;
	}
	str[i] = '\0';
}

char	*ft_itoa(long n)
{
	int		i;
	long	p;	
	char	*str;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	p = ft_poweroftens(n);
	str = ft_itoa_malloc(n, p);
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		n = -n;
		i++;
	}
	ft_fill(str, i, n, p);
	return (str);
}
