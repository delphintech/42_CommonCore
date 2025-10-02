/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:48:39 by magahat           #+#    #+#             */
/*   Updated: 2024/11/19 16:42:37 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_hand(t_cub *cub, t_img *sprite_frame, int lim_x, int lim_y)
{
	int		x;
	int		y;
	char	*pixel;
	char	*is_color;

	x = lim_x;
	while (x < LENGTH && x - lim_x < cub->data.tex.sprite.width)
	{
		y = lim_y;
		while (y < HEIGHT && y - lim_y < cub->data.tex.sprite.height)
		{
			pixel = cub->data.map->addr + x * (cub->data.map->pixel_bits / 8)
				+ y * cub->data.map->line_size;
			is_color = (sprite_frame->addr + ((y - lim_y) * 1000 / HEIGHT
						* sprite_frame->line_size + (x - lim_x) * 1920 / LENGTH
						* (sprite_frame->pixel_bits / 8)));
			if (*is_color)
				*(int *)pixel = *(int *)is_color;
			y++;
		}
		x++;
	}
}

int	animated_sprite(t_cub *cub)
{
	int			i;
	t_sprite	*sprite;

	sprite = &cub->data.tex.sprite;
	if (sprite->delay > 10)
	{
		if (sprite->current_frame == 4)
			sprite->current_frame = 0;
		else
			sprite->current_frame += 1;
		sprite->delay = 0;
	}
	else
		sprite->delay++;
	i = cub->data.tex.sprite.current_frame;
	draw_hand(cub, &cub->data.tex.sprite.frames[i],
		LENGTH - cub->data.tex.sprite.width * LENGTH / 1920,
		HEIGHT - cub->data.tex.sprite.height * HEIGHT / 1000);
	return (0);
}

int	manage_visual(t_cub *cub)
{
	gettimeofday(&cub->data.time, NULL);
	cub->data.map = malloc(sizeof(t_img));
	if (!cub->data.map)
		exit_game(cub, "ERR_MEM: memory not allocated.\n");
	cub->data.map->img = mlx_new_image(cub->data.mlx, LENGTH, HEIGHT);
	cub->data.map->addr = mlx_get_data_addr(cub->data.map->img,
			&cub->data.map->pixel_bits, &cub->data.map->line_size,
			&cub->data.map->endian);
	raycasting(cub);
	if (LENGTH >= 960 && HEIGHT >= 500)
	{
		minimap(cub);
		animated_sprite(cub);
	}
	mlx_put_image_to_window(cub->data.mlx, cub->data.win,
		cub->data.map->img, 0, 0);
	mlx_destroy_image(cub->data.mlx, cub->data.map->img);
	free(cub->data.map);
	return (1);
}
