/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:55:09 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/02 16:27:10 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < IMG_W && y >= 0 && y < IMG_H)
	{
		pixel = img->addr + x * (img->pixel_bits / 8) + y * img->line_size;
		*(int *)pixel = color;
	}
}

void	draw_line(t_img *img, t_coord *start, t_coord *end)
{
	int			i;
	t_line		line;
	float		steps;

	line.dx = end->x - start->x;
	line.dy = end->y - start->y;
	if (abs((int)line.dx) > abs((int)line.dy))
		steps = abs((int)line.dx);
	else
		steps = abs((int)line.dy);
	set_color_grad(&line, start, end);
	line.new_x = start->x;
	line.new_y = start->y;
	line.new_color = start->color;
	i = 0;
	while (i < steps)
	{
		line.new_x = line.new_x + line.dx / (float) steps;
		line.new_y = line.new_y + line.dy / (float) steps;
		put_pixel(img, line.new_x, line.new_y, line.new_color);
		set_next_point_color(&line);
		i++;
	}
}

void	scale_to_image(t_map *map, int height, int width)
{
	if (height / (float)map->max_y < width / (float)map->max_x)
		scale(map->coords, height / (float)map->max_y, 0, 0);
	else
		scale(map->coords, width / (float)map->max_x, 0, 0);
}

void	create_img(t_data *data, t_map *map)
{
	int			x;
	int			y;
	t_coord		*coord;

	data->image.img = mlx_new_image(data->mlx, IMG_W, IMG_H);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&(data->image.pixel_bits), &(data->image.line_size),
			&(data->image.endian));
	coord = *(map->coords);
	y = 0;
	while (y < map->heigth)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != map->width - 1)
				draw_line(&(data->image), coord, coord->next);
			if (y != map->heigth - 1)
				draw_line(&(data->image), coord, find_front(coord, map->width));
			x++;
			coord = coord->next;
		}
		y++;
	}
}
