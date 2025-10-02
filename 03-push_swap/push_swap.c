/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:20:58 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/26 12:55:49 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include "push_swap.h"

void	clean_all(t_stack **sta, t_stack **stb)
{
	clean_stack(sta);
	clean_stack(stb);
}

void	push_to_stb(t_stack **sta, t_stack **stb, int level)
{
	t_stack	*node;
	int		size;
	int		i;

	node = ft_stclast(*sta);
	i = 0;
	size = ft_stcsize(*sta);
	while (i < size)
	{
		if ((node->place >> level) & 1)
			ft_r(sta, 'a');
		else
			ft_p(stb, sta, 'b');
		node = ft_stclast(*sta);
		i++;
	}
}

void	radix(t_stack **sta, t_stack **stb, int level, int max)
{
	t_stack	*node;
	int		size;
	int		i;

	push_to_stb(sta, stb, level);
	node = ft_stclast(*stb);
	size = ft_stcsize(*stb);
	i = 0;
	while (i < size)
	{
		if (max >> (level + 1) != 0 && ((node->place >> (level + 1)) & 1) == 0)
			ft_r(stb, 'b');
		else
			ft_p(sta, stb, 'a');
		node = ft_stclast(*stb);
		i++;
	}
}

void	sort(t_stack **sta, t_stack **stb)
{
	int		level;
	int		max;

	max = ft_stcsize(*sta) - 1;
	level = 0;
	if (max < 3)
		sort_three(sta);
	else if (max < 5)
		sort_five(sta, stb);
	else
	{
		while (check_sorted(sta) == 0)
		{
			radix(sta, stb, level, max);
			level++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_stack	**sta;
	t_stack	**stb;

	if (argc == 1)
		return (0);
	if (check_args(argc, argv) == 0)
		return (ft_printf("Error\n"), 0);
	stb = malloc(sizeof(t_stack *));
	sta = to_stack(argc, argv);
	*stb = NULL;
	if (!sta || !*sta || !stb || check_stack(sta) == 0)
		return (clean_all(sta, stb), ft_printf("Error\n"), 0);
	if (check_sorted(sta) == 1)
		return (clean_all(sta, stb), 0);
	add_place(sta, 0);
	sort(sta, stb);
	clean_all(sta, stb);
	return (0);
}
