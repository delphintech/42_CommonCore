/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:43:07 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 11:11:42 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_keypress(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		exit_game(cub, NULL);
	else if (keysym == XK_a)
		move_a(cub);
	else if (keysym == XK_w)
		move_w(cub);
	else if (keysym == XK_d)
		move_d(cub);
	else if (keysym == XK_s)
		move_s(cub);
	else if (keysym == XK_space)
		open_door(cub);
	else if (keysym == XK_Left)
		change_orientation(cub, -1);
	else if (keysym == XK_Right)
		change_orientation(cub, 1);
	return (0);
}

void	manage_game(t_cub *cub)
{
	start_orientation(cub);
	cub->data.mlx = mlx_init();
	if (cub->data.mlx == NULL)
		exit_clear("ERR_MLX: memory not allocated.", cub);
	open_textures(cub);
	cub->data.win = mlx_new_window(cub->data.mlx, LENGTH, HEIGHT, "cub3D");
	if (cub->data.win == NULL)
		exit_fail(cub, 1);
	if (MOUSE == TRUE)
	{
		mlx_mouse_hide(cub->data.mlx, cub->data.win);
		mlx_mouse_move(cub->data.mlx, cub->data.win, LENGTH / 2, HEIGHT / 2);
		mlx_hook(cub->data.win, MotionNotify, PointerMotionMask,
			&mouse_orientation, cub);
	}
	mlx_loop_hook(cub->data.mlx, &manage_visual, cub);
	mlx_hook(cub->data.win, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->data.win, DestroyNotify, StructureNotifyMask,
		&end_game, cub);
	mlx_loop(cub->data.mlx);
}
