/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:10:00 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/26 12:47:58 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"

void	ft_s(t_stack **stack, char print)
{
	t_stack	*first;
	t_stack	*node;
	int		swpl;
	int		swap;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	node = *stack;
	while (node->next->next)
		node = node->next;
	swap = node->nb;
	swpl = node->place;
	node->nb = node->next->nb;
	node->place = node->next->place;
	node->next->nb = swap;
	node->next->place = swpl;
	*stack = first;
	if (print != '\0')
		ft_printf("s%c\n", print);
}

void	ft_p(t_stack **st1, t_stack **st2, char print)
{
	t_stack	*nd2;

	if (!*st2)
		return ;
	nd2 = ft_stclast(*st2);
	if (nd2->prev == NULL)
		*st2 = NULL;
	if (nd2->prev != NULL)
	{
		nd2->prev->next = NULL;
		nd2->prev = NULL;
	}
	ft_stcadd_back(st1, nd2);
	if (print != '\0')
		ft_printf("p%c\n", print);
}

void	ft_r(t_stack **stack, char print)
{
	t_stack	*first;
	t_stack	*last;

	if (!(*stack) || !(*stack)->next)
		return ;
	first = *stack;
	last = ft_stclast(*stack);
	last->prev->next = NULL;
	last->prev = NULL;
	last->next = first;
	first->prev = last;
	*stack = last;
	if (print != '\0')
		ft_printf("r%c\n", print);
}

void	ft_rr(t_stack **stack, char print)
{
	t_stack	*new_first;
	t_stack	*first;
	t_stack	*last;

	if (!(*stack) || !(*stack)->next)
		return ;
	first = *stack;
	new_first = first->next;
	last = ft_stclast(*stack);
	new_first->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	*stack = new_first;
	if (print != '\0')
		ft_printf("rr%c\n", print);
}
