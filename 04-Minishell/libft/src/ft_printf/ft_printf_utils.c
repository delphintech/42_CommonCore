/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:14:05 by magahat           #+#    #+#             */
/*   Updated: 2024/09/04 14:05:51 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	print_str(char *str, int fd)
{
	if (!str)
		return (ft_putstr_fd("(null)", fd), 6);
	return (ft_putstr_fd(str, fd), ft_strlen(str));
}

int	print_nb(long long n, int indic, int fd)
{
	int	len_base;

	len_base = 16;
	if (indic == 1)
	{
		ft_putnbr_base_fd(n, "0123456789", fd);
		len_base = 10;
	}
	else if (indic == 2)
		ft_putnbr_base_fd(n, "0123456789ABCDEF", fd);
	else if (indic == 3)
		ft_putnbr_base_fd(n, "0123456789abcdef", fd);
	return (ft_intlen_base(n, len_base));
}
