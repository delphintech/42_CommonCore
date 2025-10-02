/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:33:56 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/20 13:43:09 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_stcsize(t_stack *stc)
{
	int	i;

	if (!stc)
		return (0);
	i = 1;
	while (stc->next != NULL)
	{
		i += 1;
		stc = stc->next;
	}
	return (i);
}

t_stack	*ft_stclast(t_stack *stc)
{
	if (!stc)
		return (NULL);
	while (stc->next != NULL)
		stc = stc->next;
	return (stc);
}

t_stack	*ft_stcnew(int nb)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->nb = nb;
	new->place = -1;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_stcadd_back(t_stack **stc, t_stack *new)
{
	t_stack	*last;

	if (!new)
		return ;
	last = ft_stclast(*stc);
	if (last == NULL)
	{
		*stc = new;
		return ;
	}
	last->next = new;
	new->prev = last;
}

void	ft_stcadd_front(t_stack **stc, t_stack *new)
{
	new->next = *stc;
	if (*stc)
		(*stc)->prev = new;
	*stc = new;
}
