/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:00:18 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 10:50:20 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*put_texture(t_cub *cub, t_ray ray)
{
	t_img	texture;

	if (ray.hit == 2)
		texture = cub->data.tex.door;
	else if (ray.side == 0)
	{
		if (ray.raydir_x > 0)
			texture = cub->data.tex.south;
		else
			texture = cub->data.tex.north;
	}
	else if (ray.side == 1)
	{
		if (ray.raydir_y < 0)
			texture = cub->data.tex.east;
		else
			texture = cub->data.tex.west;
	}
	return (texture.addr + (ray.tex_y * texture.line_size + ray.tex_x
			* (texture.pixel_bits / 8)));
}

void	cursor_mouse(t_cub *cub)
{
	char	*pixel;
	char	*is_color;
	int		line;
	int		col;

	col = LENGTH / 2 - 13;
	while (col < LENGTH / 2 + 13)
	{
		line = HEIGHT / 2 - 13;
		while (line < HEIGHT / 2 + 13)
		{
			pixel = cub->data.map->addr + col * (cub->data.map->pixel_bits / 8)
				+ line * cub->data.map->line_size;
			is_color = (cub->data.tex.cursor.addr + ((line - (HEIGHT / 2 - 13))
						* cub->data.tex.cursor.line_size
						+ (col - (LENGTH / 2 - 13))
						* (cub->data.tex.cursor.pixel_bits / 8)));
			if (*is_color)
				*(int *)pixel = *(int *)is_color;
			line++;
		}
		col++;
	}
}

void	draw_map(int col, t_cub *cub, int start, int end)
{
	int		i;
	char	*pixel;
	t_ray	ray;

	ray = cub->ray;
	i = 0;
	ray.tex_pos = (start - HEIGHT / 2 + ray.line_h / 2) * ray.step;
	while (i < HEIGHT)
	{
		pixel = cub->data.map->addr + col * (cub->data.map->pixel_bits / 8)
			+ i * cub->data.map->line_size;
		if (i < start)
			*(int *)pixel = cub->ceiling;
		else if (i >= end)
			*(int *)pixel = cub->floor;
		else
		{
			ray.tex_y = (int)ray.tex_pos;
			ray.tex_pos += ray.step;
			*(int *)pixel = *(int *)put_texture(cub, ray);
		}
		i++;
	}
	cursor_mouse(cub);
}
