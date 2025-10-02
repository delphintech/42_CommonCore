/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:32:28 by magahat           #+#    #+#             */
/*   Updated: 2024/11/19 16:42:27 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(t_cub *cub, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x >= 0 && x < MINI_SIZE && y >= 0 && y < MINI_SIZE)
	{
		pixel = cub->data.map->addr + (50 + y) * (cub->data.map->pixel_bits / 8)
			+ (HEIGHT - MINI_SIZE - 80 + x) * cub->data.map->line_size;
		*(int *)pixel = color;
	}
}

void	put_tile(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	x = x * 8;
	y = y * 8;
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (pow((x + i) - MINI_SIZE / 2, 2)
				+ pow((y + j) - MINI_SIZE / 2, 2) < pow(MINI_SIZE / 2, 2))
				put_pixel(cub, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_img player, t_cub *cub)
{
	char	*pixel;
	char	*is_color;
	int		x;
	int		y;

	x = cub->mini_x;
	while (x < cub->mini_x + 8)
	{
		y = cub->mini_y;
		while (y < cub->mini_y + 8)
		{
			pixel = cub->data.map->addr + x * (cub->data.map->pixel_bits / 8)
				+ y * cub->data.map->line_size;
			is_color = (player.addr + ((y - cub->mini_y)
						* player.line_size + (x - cub->mini_x)
						* (player.pixel_bits / 8)));
			if (*is_color)
				*(int *)pixel = *(int *)is_color;
			y++;
		}
		x++;
	}
}

void	put_player(t_cub *cub)
{
	t_img	player;

	if (cub->orientation == 'N')
		player = cub->data.tex.p_north;
	else if (cub->orientation == 'S')
		player = cub->data.tex.p_south;
	else if (cub->orientation == 'W')
		player = cub->data.tex.p_west;
	else
		player = cub->data.tex.p_east;
	draw_player(player, cub);
}

void	draw_minimap(char **centered, t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (centered[i])
	{
		j = 0;
		while (centered[i][j])
		{
			if (centered[i][j] == ' ')
				put_tile(cub, i, j, 0xe4f0ff);
			if (ft_charcmp(centered[i][j], "0NSWE") > 0)
				put_tile(cub, i, j, 0xbcc2d7);
			if (ft_charcmp(centered[i][j], "NSWE") > 0)
				put_player(cub);
			if (centered[i][j] == '1')
				put_tile(cub, i, j, 0x634100);
			if (centered[i][j] == 'D')
				put_tile(cub, i, j, 0xe39e21);
			j++;
		}
		i++;
	}
	clear_tab(centered);
}
