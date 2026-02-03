/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:04 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/01 17:07:01 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_coord	*new_coord(int x, int y, int z, int color)
{
	t_coord	*new;

	new = (t_coord *)malloc(sizeof(t_coord));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->color = color;
	new->next = NULL;
	return (new);
}

void	coord_add_back(t_coord **coords, t_coord *new)
{
	t_coord	*last;

	if (!new || !coords)
		return ;
	last = *coords;
	if (!last)
	{
		*coords = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

int	find_min_x(t_coord **coords)
{
	t_coord	*temp;
	int		min;

	temp = *coords;
	min = temp->x;
	while (temp)
	{
		if (temp->x < min)
			min = temp->x;
		temp = temp->next;
	}
	return (min);
}

int	find_min_y(t_coord **coords)
{
	t_coord	*temp;
	int		min;

	temp = *coords;
	min = temp->y;
	while (temp)
	{
		if (temp->y < min)
			min = temp->y;
		temp = temp->next;
	}
	return (min);
}

t_coord	*find_front(t_coord *coord, int line_size)
{
	int			i;
	t_coord		*front;

	front = coord;
	i = 0;
	while (front && i < line_size)
	{
		front = front->next;
		i++;
	}
	return (front);
}
