/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:08:41 by magahat           #+#    #+#             */
/*   Updated: 2024/11/19 11:49:04 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	move_player(t_cub *cub, int x, int y)
{
	if (cub->map[x][y] == '1' || cub->map[x][y] == 'D')
		return (0);
	cub->map[cub->player_x][cub->player_y] = '0';
	cub->map[x][y] = cub->orientation;
	return (1);
}

void	move_w(t_cub *cub)
{
	double	move_x;
	double	move_y;

	move_x = cub->data.dir_x * cub->data.move_speed;
	move_y = cub->data.dir_y * cub->data.move_speed;
	if (move_player(cub, (int)(cub->data.pl_x + move_x), cub->data.pl_y))
		cub->data.pl_x += move_x;
	if (move_player(cub, cub->data.pl_x, (int)(cub->data.pl_y + move_y)))
		cub->data.pl_y += move_y;
	cub->player_x = (int)cub->data.pl_x;
	cub->player_y = (int)cub->data.pl_y;
}

void	move_s(t_cub *cub)
{
	double	move_x;
	double	move_y;

	move_x = cub->data.dir_x * cub->data.move_speed;
	move_y = cub->data.dir_y * cub->data.move_speed;
	if (move_player(cub, (int)(cub->data.pl_x - move_x), cub->data.pl_y))
		cub->data.pl_x -= move_x;
	if (move_player(cub, cub->data.pl_x, (int)(cub->data.pl_y - move_y)))
		cub->data.pl_y -= move_y;
	cub->player_x = (int)cub->data.pl_x;
	cub->player_y = (int)cub->data.pl_y;
}

void	move_a(t_cub *cub)
{
	double	move_x;
	double	move_y;

	move_x = cub->data.dir_x * cub->data.move_speed;
	move_y = cub->data.dir_y * cub->data.move_speed;
	if (move_player(cub, cub->data.pl_x, (int)(cub->data.pl_y + move_x)))
			cub->data.pl_y += move_x;
	if (move_player(cub, (int)(cub->data.pl_x - move_y), cub->data.pl_y))
		cub->data.pl_x -= move_y;
	cub->player_x = (int)cub->data.pl_x;
	cub->player_y = (int)cub->data.pl_y;
}

void	move_d(t_cub *cub)
{
	double	move_x;
	double	move_y;

	move_x = cub->data.dir_x * cub->data.move_speed;
	move_y = cub->data.dir_y * cub->data.move_speed;
	if (move_player(cub, cub->data.pl_x, (int)(cub->data.pl_y - move_x)))
			cub->data.pl_y -= move_x;
	if (move_player(cub, (int)(cub->data.pl_x + move_y), cub->data.pl_y))
		cub->data.pl_x += move_y;
	cub->player_x = (int)cub->data.pl_x;
	cub->player_y = (int)cub->data.pl_y;
}

/* void	movement(t_cub *cub, char c)
{
	double	x;
	double	y;
	double	move_x;
	double	move_y;
	
	move_x = cub->data.dir_x * cub->data.move_speed;
	move_y = cub->data.dir_y * cub->data.move_speed;
	x = cub->data.pl_x;
	y = cub->data.pl_y;
	if (c == 'W')
	{
		if (move_player(cub, (int)(x + move_x), y))
			x += move_x;
		if (move_player(cub, x, (int)(y + move_y)))
			y += move_y;
	}
	else if (c == 'S')
	{
		if (move_player(cub, (int)(x - move_x), y))
			x -= move_x;
		if (move_player(cub, x, (int)(y - move_y)))
			y -= move_y;
	}
	else if (c == 'A')
	{
		if (move_player(cub, x, (int)(y + move_x)))
			y += move_x;
		if (move_player(cub, (int)(x - move_y), y))
			x -= move_y;
	}
	else if (c == 'D')
	{
		if (move_player(cub, x, (int)(y - move_x)))
			y -= move_x;
		if (move_player(cub, (int)(x + move_y), y))
			x += move_y;
	}
	cub->player_x = (int)x;
	cub->player_y = (int)y;
	cub->data.pl_x = x;
	cub->data.pl_y = y;
}
 */