/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:36:58 by magahat           #+#    #+#             */
/*   Updated: 2024/09/06 12:03:53 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	check_variable(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '%')
			i++;
		else if (str[i] == '%' && ft_charcmp(str[i + 1], "cpusdixX%"))
			i += 2;
		else
			return (0);
	}
	return (1);
}

static int	print_pointer(void *ptr, int fd)
{
	if (ptr)
	{
		ft_putstr_fd("0x", fd);
		return (print_nb((unsigned long)ptr, 3, fd) + 2);
	}
	return (ft_putstr_fd("(nil)", fd), 5);
}

static int	ft_conversion(char c, va_list variable, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd((int)va_arg(variable, int), fd), 1);
	if (c == '%')
		return (ft_putchar_fd(c, fd), 1);
	if (c == 's')
		return (print_str((char *)va_arg(variable, const char *), fd));
	if (c == 'p')
		return (print_pointer(va_arg(variable, void *), fd));
	if (c == 'd' || c == 'i')
		return (print_nb((long)va_arg(variable, int), 1, fd));
	if (c == 'u')
		return (print_nb((long)va_arg(variable, unsigned int), 1, fd));
	if (c == 'X')
		return (print_nb((unsigned int)va_arg(variable, int), 2, fd));
	if (c == 'x')
		return (print_nb((unsigned int)va_arg(variable, int), 3, fd));
	return (0);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	int			count;
	int			i;
	va_list		variable;

	va_start(variable, str);
	count = 0;
	i = 0;
	if (!str || !check_variable(str))
		return (ft_putstr_fd("warning input\n", 2), -1);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i++], fd);
			count++;
		}
		else
		{
			count += ft_conversion(str[i + 1], variable, fd);
			i += 2;
		}
	}
	va_end(variable);
	return (count);
}
