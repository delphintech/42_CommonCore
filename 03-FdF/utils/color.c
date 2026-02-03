/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:10:21 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/02 15:26:40 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_map_color(t_map *map)
{
	int		steps;
	t_coord	*temp;

	steps = (map->max_z - map->min_z) / 3;
	temp = *(map->origins);
	while (temp)
	{
		if (temp->color == 0xffffff)
		{
			if (temp->z < -steps * 2)
				temp->color = 0x5CB270;
			else if (temp->z < -steps)
				temp->color = 0x88C696;
			else if (temp->z < 0)
				temp->color = 0xB3DABC;
			else if (temp->z > steps * 2)
				temp->color = 0x0D41E1;
			else if (temp->z > steps)
				temp->color = 0x3863E6;
			else if (temp->z > 0)
				temp->color = 0x8FA7F0;
		}
		temp = temp->next;
	}
}

void	set_color_grad(t_line *line, t_coord *start, t_coord *end)
{
	int		steps;

	if (abs((int)line->dx) > abs((int)line->dy))
		steps = abs((int)line->dx);
	else
		steps = abs((int)line->dy);
	if (steps == 0)
	{
		line->grad_red = 0;
		line->grad_green = 0;
		line->grad_blue = 0;
	}
	else
	{
		line->grad_red = ((end->color >> 16) - (start->color >> 16)) / steps;
		line->grad_green = (((end->color >> 8) & 0xFF)
				- ((end->color >> 8) & 0xFF)) / steps;
		line->grad_blue = ((end->color & 0xFF) - (start->color & 0xFF)) / steps;
	}
}

void	set_next_point_color(t_line *line)
{
	int	red;
	int	green;
	int	blue;

	red = (line->new_color >> 16) + line->grad_red;
	green = ((line->new_color >> 8) & 0xFF) + line->grad_blue;
	blue = (line->new_color & 0xFF) + line->grad_green;
	line->new_color = red << 16;
	line->new_color += green << 8;
	line->new_color += blue;
}
