/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:15:12 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/26 12:23:53 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	check_stack(t_stack	**stack)
{
	t_stack	*node;
	t_stack	*temp;

	if (!(*stack))
		return (0);
	node = *stack;
	while (node->next)
	{
		temp = node->next;
		while (temp)
		{
			if (temp->nb == node->nb)
				return (0);
			temp = temp->next;
		}
		node = node->next;
	}
	return (1);
}

void	clean_stack(t_stack **stack)
{
	t_stack	*temp;

	if (!stack)
		return ;
	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
	free(stack);
}

t_stack	**to_stack(int argc, char **argv)
{
	int		i;
	int		j;
	char	**tab;
	t_stack	**list;
	t_stack	*new;

	list = malloc(sizeof(t_stack *));
	if (!list)
		return (NULL);
	*list = NULL;
	i = 0;
	while (++i < argc)
	{
		tab = ft_split(argv[i], ' ');
		j = 0;
		while (tab[j])
		{
			new = ft_stcnew(ft_atoi(tab[j]));
			ft_stcadd_front(list, new);
			j++;
		}
		clean_tab(tab);
	}
	return (list);
}

void	add_place(t_stack **stack, int place)
{
	t_stack	*node;
	t_stack	*min;

	node = *stack;
	while (node->place != -1)
	{
		node = node->next;
		if (!node)
			return ;
	}
	min = node;
	while (node)
	{
		if (node->place == -1 && node->nb < min->nb)
			min = node;
		node = node->next;
	}
	min->place = place;
	add_place(stack, place + 1);
}

int	check_sorted(t_stack **stack)
{
	t_stack	*node;

	if (!stack || !*(stack))
		return (1);
	node = *stack;
	while (node)
	{
		if (node->next == NULL)
			return (1);
		if (node->nb < node->next->nb)
			return (0);
		node = node->next;
	}
	return (1);
}
