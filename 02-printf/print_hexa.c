/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:12:26 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/05 13:39:27 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int	hexa_size(unsigned long nb)
{
	int				s;
	unsigned long	p;

	s = 1;
	p = 1;
	while (p <= nb / 16)
	{
		s += 1;
		p *= 16;
	}
	return (s);
}

int	print_hexa(unsigned int nb)
{
	char				*base;
	int					count;
	unsigned int		p;

	if (nb == 0)
		return (ft_putchar('0'));
	base = "0123456789abcdef";
	count = hexa_size(nb);
	p = 1;
	while (p <= nb / 16)
		p *= 16;
	while (p > 0)
	{
		ft_putchar(base[nb / p]);
		nb %= p;
		p /= 16;
	}
	return (count);
}

int	print_hexa_upper(unsigned int nb)
{
	char				*base;
	int					count;
	unsigned int		p;

	if (nb == 0)
		return (ft_putchar('0'));
	base = "0123456789ABCDEF";
	count = hexa_size(nb);
	p = 1;
	while (p <= nb / 16)
		p *= 16;
	while (p > 0)
	{
		ft_putchar(base[nb / p]);
		nb %= p;
		p /= 16;
	}
	return (count);
}

int	print_pointer(unsigned long int pointer)
{
	char					*base;
	int						count;
	unsigned long int		p;

	if (pointer == 0)
		return (ft_putlstr("(nil)", 5));
	base = "0123456789abcdef";
	ft_putlstr("0x", 2);
	count = hexa_size(pointer) + 2;
	p = 1;
	while (p <= pointer / 16)
		p *= 16;
	while (p > 0)
	{
		ft_putchar(base[pointer / p]);
		pointer %= p;
		p /= 16;
	}
	return (count);
}
