/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:54:16 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/02 15:24:48 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_percent(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == '%')
			return (i);
		i++;
	}
	return (i);
}

int	print_args(va_list args, char type)
{
	if (type == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (type == 'p')
		return (print_pointer(va_arg(args, unsigned long)));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (type == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (type == 'x')
		return (print_hexa(va_arg(args, unsigned long)));
	else if (type == 'X')
		return (print_hexa_upper(va_arg(args, unsigned long)));
	else if (type == '%')
		return (ft_putchar('%'));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;
	int		start;

	count = 0;
	start = 0;
	i = 0;
	va_start(args, str);
	while (start < (int)ft_strlen(str))
	{
		i = find_percent(str, start);
		count += ft_putlstr(&str[start], i - start);
		if (i < (int)ft_strlen(str))
			count += print_args(args, str[i + 1]);
		start = i + 2;
	}
	va_end(args);
	return (count);
}
