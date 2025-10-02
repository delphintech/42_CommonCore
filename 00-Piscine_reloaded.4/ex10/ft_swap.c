/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:30:41 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/14 10:04:10 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	ft_swap(int *a, int *b)
{
	int	buf;

	buf = *a;
	*a = *b;
	*b = buf;
}

/*
int	main(int ac, char** av)
{
	int	a;
	int b;
	int	*pb;
	int	*pa;

	(void)ac;
	a = atoi(av[1]);
	b = atoi(av[2]);
	pa = &a;
	pb = &b;
	printf("(Initials) a:%d, b:%d\n", a, b);
	ft_swap(pa, pb);
	printf("(Swaped) a:%d, b:%d\n", a, b);
}
*/