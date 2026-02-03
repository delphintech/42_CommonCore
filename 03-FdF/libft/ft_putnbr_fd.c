/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:52:04 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/21 17:30:41 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static long	ft_poweroftens(int n)
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

void	ft_putnbr_fd(int n, int fd)
{
	long	p;	
	char	num;

	p = ft_poweroftens(n);
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	while (p > 0)
	{
		num = n / p + '0';
		write(fd, &num, 1);
		n = n % p;
		p = p / 10;
	}
}
