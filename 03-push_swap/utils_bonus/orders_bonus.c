/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orders_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:40:34 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/26 12:48:29 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker_bonus.h"
#include <stdlib.h>

void	clean_orders(t_list **order)
{
	t_list	*temp;

	if (!order)
		return ;
	while (*order)
	{
		temp = (*order)->next;
		if ((*order)->content)
			free((*order)->content);
		free(*order);
		(*order) = temp;
	}
	free(order);
}

t_list	**get_orders(void)
{
	char	*line;
	t_list	**list;
	t_list	*new;

	list = malloc(sizeof(t_list *));
	if (!list)
		return (NULL);
	*list = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			return (list);
		new = ft_lstnew(line);
		ft_lstadd_back(list, new);
	}
	return (list);
}

int	check_orders(t_list **order)
{
	t_list	*temp;

	if (!(*order))
		return (1);
	temp = *order;
	while (temp)
	{
		if (ft_strncmp(temp->content, "sa\n", 6) == 0
			|| ft_strncmp(temp->content, "sb\n", 6) == 0
			|| ft_strncmp(temp->content, "ss\n", 6) == 0
			|| ft_strncmp(temp->content, "pa\n", 6) == 0
			|| ft_strncmp(temp->content, "pb\n", 6) == 0
			|| ft_strncmp(temp->content, "ra\n", 6) == 0
			|| ft_strncmp(temp->content, "rb\n", 6) == 0
			|| ft_strncmp(temp->content, "rr\n", 6) == 0
			|| ft_strncmp(temp->content, "rra\n", 6) == 0
			|| ft_strncmp(temp->content, "rrb\n", 6) == 0
			|| ft_strncmp(temp->content, "rrr\n", 6) == 0)
			temp = temp->next;
		else
			return (0);
	}
	return (1);
}

void	apply_orders(t_stack **stack, t_stack **b, t_list **order)
{
	char	*str;
	t_list	*temp;

	temp = *order;
	while (temp)
	{
		str = temp->content;
		if (ft_strncmp(str, "sa\n", 3) == 0 || ft_strncmp(str, "ss\n", 3) == 0)
			ft_s(stack, '\0');
		if (ft_strncmp(str, "sb\n", 3) == 0 || ft_strncmp(str, "ss\n", 3) == 0)
			ft_s(b, '\0');
		if (ft_strncmp(str, "pa\n", 3) == 0)
			ft_p(stack, b, '\0');
		if (ft_strncmp(str, "pb\n", 3) == 0)
			ft_p(b, stack, '\0');
		if (ft_strncmp(str, "ra\n", 3) == 0 || ft_strncmp(str, "rr\n", 3) == 0)
			ft_r(stack, '\0');
		if (ft_strncmp(str, "rb\n", 3) == 0 || ft_strncmp(str, "rr\n", 3) == 0)
			ft_r(b, '\0');
		if (ft_strncmp(str, "rra\n", 4) == 0 || ft_strncmp(str, "rrr\n", 4) == 0)
			ft_rr(stack, '\0');
		if (ft_strncmp(str, "rrb\n", 4) == 0 || ft_strncmp(str, "rrr\n", 4) == 0)
			ft_rr(b, '\0');
		temp = temp->next;
	}
}
