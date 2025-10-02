/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:36:53 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/25 16:27:04 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*find_min(t_stack **stack)
{
	t_stack		*node;
	t_stack		*min;

	node = *stack;
	min = node;
	while (node)
	{
		if (min->nb > node->nb)
			min = node;
		node = node->next;
	}
	return (min);
}

void	smart_rotate(t_stack **stack, int place, char stc)
{
	int		size;
	int		spot;
	t_stack	*node;

	size = ft_stcsize(*stack);
	node = *stack;
	spot = 0;
	if (!node)
		return ;
	while (++spot && node->place != place)
		node = node->next;
	if (size - spot > size / 2)
	{
		while (spot-- && spot >= 0)
			ft_rr(stack, stc);
	}
	else
	{
		while (size - spot > 0)
		{
			ft_r(stack, stc);
			spot++;
		}
	}
}

void	sort_three(t_stack **stc)
{
	if (check_sorted(stc) == 1)
		return ;
	if (ft_stcsize(*stc) == 2)
	{
		if ((*stc)->place < (*stc)->next->place)
			ft_s(stc, 'a');
	}
	else if ((*stc)->nb > (*stc)->next->nb && (*stc)->nb > ft_stclast(*stc)->nb)
		ft_s(stc, 'a');
	else if ((*stc)->nb > (*stc)->next->nb && (*stc)->nb < ft_stclast(*stc)->nb)
		ft_r(stc, 'a');
	else if ((*stc)->nb < (*stc)->next->nb && (*stc)->nb > ft_stclast(*stc)->nb)
	{
		ft_rr(stc, 'a');
		ft_s(stc, 'a');
	}
	else if ((*stc)->nb < (*stc)->next->nb
		&& (*stc)->next->nb < ft_stclast(*stc)->nb)
	{
		ft_r(stc, 'a');
		ft_s(stc, 'a');
	}
	else if ((*stc)->nb < (*stc)->next->nb
		&& (*stc)->next->nb > ft_stclast(*stc)->nb)
		ft_rr(stc, 'a');
}

void	sort_five(t_stack **sta, t_stack **stb)
{
	smart_rotate(sta, find_min(sta)->place, 'a');
	ft_p(stb, sta, 'b');
	if (ft_stcsize(*sta) == 4)
	{
		smart_rotate(sta, find_min(sta)->place, 'a');
		ft_p(stb, sta, 'b');
	}
	sort_three(sta);
	ft_p(sta, stb, 'a');
	ft_p(sta, stb, 'a');
}
