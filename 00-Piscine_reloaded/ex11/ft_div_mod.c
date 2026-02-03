/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:57:43 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/14 10:07:55 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a / b;
	*mod = a % b;
}

/*
int	main(int ac, char **av)
{
	int	a;
	int b;
	int	d;
	int	m;
	int	*div;
	int	*mod;
	
	(void)ac;
	a = atoi(av[1]);
	b = atoi(av[2]);
	div = &d;
	mod = &m;
	printf("(Initials) a:%d, b:%d\n", a, b);
	ft_div_mod(a, b, div, mod);
	printf("(div_mod) div:%d, mod:%d\n", d, m);
}
*/