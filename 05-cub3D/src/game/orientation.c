/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:30:39 by magahat           #+#    #+#             */
/*   Updated: 2024/11/12 14:52:56 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	start_orientation(t_cub *cub)
{
	cub->data.dir_x = 0;
	cub->data.dir_y = 0;
	cub->data.plane_x = 0.0;
	cub->data.plane_y = 0.0;
	if (cub->orientation == 'N')
	{
		cub->data.dir_x = -1;
		cub->data.plane_y = FOV;
	}
	else if (cub->orientation == 'S')
	{
		cub->data.dir_x = 1;
		cub->data.plane_y = -FOV;
	}
	else if (cub->orientation == 'W')
	{
		cub->data.dir_y = -1;
		cub->data.plane_x = -FOV;
	}
	else if (cub->orientation == 'E')
	{
		cub->data.dir_y = 1;
		cub->data.plane_x = FOV;
	}
}

void	orientation_game(t_cub *cub)
{
	if (cub->data.dir_x < -0.5 && cub->data.dir_y < 0.5
		&& cub->data.dir_y > -0.5)
		cub->orientation = 'N';
	else if (cub->data.dir_x > 0.5 && cub->data.dir_y < 0.5
		&& cub->data.dir_y > -0.5)
		cub->orientation = 'S';
	else if (cub->data.dir_y < -0.5 && cub->data.dir_x < 0.5
		&& cub->data.dir_x > -0.5)
		cub->orientation = 'W';
	else if (cub->data.dir_y > 0.5 && cub->data.dir_x > -0.5
		&& cub->data.dir_x < 0.5)
		cub->orientation = 'E';
}

void	change_orientation(t_cub *cub, int indic)
{
	cub->data.dir_tmp = cub->data.dir_x;
	cub->data.plane_tmp = cub->data.plane_x;
	if (indic == 1)
	{
		cub->data.dir_x = cub->data.dir_x * cos(-cub->data.rot_speed)
			- cub->data.dir_y * sin(-cub->data.rot_speed);
		cub->data.dir_y = cub->data.dir_tmp * sin(-cub->data.rot_speed)
			+ cub->data.dir_y * cos(-cub->data.rot_speed);
		cub->data.plane_x = cub->data.plane_x * cos(-cub->data.rot_speed)
			- cub->data.plane_y * sin(-cub->data.rot_speed);
		cub->data.plane_y = cub->data.plane_tmp * sin(-cub->data.rot_speed)
			+ cub->data.plane_y * cos(-cub->data.rot_speed);
	}
	else
	{
		cub->data.dir_x = cub->data.dir_x * cos(cub->data.rot_speed)
			- cub->data.dir_y * sin(cub->data.rot_speed);
		cub->data.dir_y = cub->data.dir_tmp * sin(cub->data.rot_speed)
			+ cub->data.dir_y * cos(cub->data.rot_speed);
		cub->data.plane_x = cub->data.plane_x * cos(cub->data.rot_speed)
			- cub->data.plane_y * sin(cub->data.rot_speed);
		cub->data.plane_y = cub->data.plane_tmp * sin(cub->data.rot_speed)
			+ cub->data.plane_y * cos(cub->data.rot_speed);
	}
	orientation_game(cub);
}

int	mouse_orientation(int x, int y, t_cub *cub)
{
	cub->data.rot_speed = cub->data.fps * 2.0;
	(void)y;
	if (x < LENGTH / 2)
		change_orientation(cub, -1);
	else if (x > LENGTH / 2)
		change_orientation(cub, 1);
	mlx_mouse_move(cub->data.mlx, cub->data.win, LENGTH / 2, HEIGHT / 2);
	return (0);
}
