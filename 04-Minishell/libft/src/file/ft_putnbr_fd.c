/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:26:57 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:01:02 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	val;
	char			c;

	if (n < 0)
	{
		val = -n;
		write(fd, "-", 1);
	}
	else
		val = n;
	if (val < 10)
	{
		c = '0' + val;
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(val / 10, fd);
		ft_putnbr_fd(val % 10, fd);
	}
}
