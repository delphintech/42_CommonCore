/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:43:18 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 10:59:38 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_img	texture_w_addr(t_cub *cub, char *path, int tex_h, int tex_w)
{
	t_img	tex;

	tex.img = NULL;
	tex.img = mlx_xpm_file_to_image(cub->data.mlx, path, &tex_w, &tex_h);
	if (!tex.img)
		return (tex);
	tex.addr = mlx_get_data_addr(tex.img, &tex.pixel_bits,
			&tex.line_size, &tex.endian);
	return (tex);
}

void	init_sprite(t_cub *cub)
{
	int			i;
	t_sprite	*sprite;

	sprite = &cub->data.tex.sprite;
	sprite->height = 900;
	sprite->width = 600;
	sprite->frames[0] = texture_w_addr(cub, TORCH_1, 900, 600);
	sprite->frames[1] = texture_w_addr(cub, TORCH_2, 900, 600);
	sprite->frames[2] = texture_w_addr(cub, TORCH_3, 900, 600);
	sprite->frames[3] = texture_w_addr(cub, TORCH_4, 900, 600);
	sprite->frames[4] = texture_w_addr(cub, TORCH_5, 900, 600);
	sprite->frames[5].img = NULL;
	i = 0;
	while (i < 5)
		if (!sprite->frames[i++].img)
			exit_fail(cub, 3);
	sprite->delay = 0;
	sprite->current_frame = 0;
}

void	open_textures(t_cub *cub)
{
	cub->data.tex.door = texture_w_addr(cub, DOOR_PATH, TEX_H, TEX_W);
	cub->data.tex.north = texture_w_addr(cub, cub->north, TEX_H, TEX_W);
	cub->data.tex.south = texture_w_addr(cub, cub->south, TEX_H, TEX_W);
	cub->data.tex.east = texture_w_addr(cub, cub->east, TEX_H, TEX_W);
	cub->data.tex.west = texture_w_addr(cub, cub->west, TEX_H, TEX_W);
	cub->data.tex.cursor = texture_w_addr(cub, CURSOR_PATH, 26, 26);
	cub->data.tex.p_north = texture_w_addr(cub, PLAYER_N, 8, 8);
	cub->data.tex.p_south = texture_w_addr(cub, PLAYER_S, 8, 8);
	cub->data.tex.p_east = texture_w_addr(cub, PLAYER_E, 8, 8);
	cub->data.tex.p_west = texture_w_addr(cub, PLAYER_W, 8, 8);
	init_sprite(cub);
	if (!cub->data.tex.door.img || !cub->data.tex.p_north.img
		|| !cub->data.tex.p_south.img || !cub->data.tex.p_east.img
		|| !cub->data.tex.p_west.img || !cub->data.tex.cursor.img)
		exit_fail(cub, 3);
	if (!cub->data.tex.north.img || !cub->data.tex.south.img
		|| !cub->data.tex.east.img || !cub->data.tex.west.img)
		exit_fail(cub, 2);
}

void	close_sprite(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (cub->data.tex.sprite.frames[i].img)
			mlx_destroy_image(cub->data.mlx,
				cub->data.tex.sprite.frames[i].img);
		i++;
	}
}

void	close_textures(t_cub *cub)
{
	if (cub->data.tex.door.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.door.img);
	if (cub->data.tex.north.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.north.img);
	if (cub->data.tex.south.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.south.img);
	if (cub->data.tex.east.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.east.img);
	if (cub->data.tex.west.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.west.img);
	if (cub->data.tex.cursor.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.cursor.img);
	if (cub->data.tex.p_north.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.p_north.img);
	if (cub->data.tex.p_south.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.p_south.img);
	if (cub->data.tex.p_east.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.p_east.img);
	if (cub->data.tex.p_west.img)
		mlx_destroy_image(cub->data.mlx, cub->data.tex.p_west.img);
	close_sprite(cub);
}
