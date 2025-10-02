/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:26:57 by magahat           #+#    #+#             */
/*   Updated: 2024/09/04 14:17:21 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putnbr_base_fd(long long n, char *base, int fd)
{
	int		len_base;

	len_base = ft_strlen(base);
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n < len_base)
		write(fd, &base[n], 1);
	else
	{
		ft_putnbr_base_fd(n / len_base, base, fd);
		ft_putnbr_base_fd(n % len_base, base, fd);
	}
}
