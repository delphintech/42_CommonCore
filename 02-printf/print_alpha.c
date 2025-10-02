/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:00:01 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/05 13:07:26 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	l;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	l = ft_strlen(str);
	write(1, str, l);
	return (l);
}

int	ft_putlstr(const char *str, int length)
{
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, str, length);
	return (length);
}

int	ft_putnbr(int num)
{
	int		count;
	char	*nbs;

	nbs = ft_itoa((long)num);
	count = ft_putlstr(nbs, ft_strlen(nbs));
	free(nbs);
	return (count);
}

int	ft_putunsigned(unsigned int num)
{
	int		count;
	char	*nbs;

	nbs = ft_itoa((long)num);
	count = ft_putlstr(nbs, ft_strlen(nbs));
	free(nbs);
	return (count);
}
