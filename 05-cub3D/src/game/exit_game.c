/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:42:46 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 10:33:14 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	exit_game(t_cub *cub, char *msg)
{
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	mlx_loop_end(cub->data.mlx);
	close_textures(cub);
	mlx_destroy_display(cub->data.mlx);
	free(cub->data.mlx);
	clear_cub(cub);
	if (msg)
		exit_clear(msg, NULL);
	else
		exit (EXIT_SUCCESS);
}

int	end_game(t_cub *cub)
{
	exit_game(cub, NULL);
	return (0);
}

void	exit_fail(t_cub *cub, int indic)
{
	mlx_loop_end(cub->data.mlx);
	close_textures(cub);
	mlx_destroy_display(cub->data.mlx);
	free(cub->data.mlx);
	if (indic == 1)
		exit_clear("ERR_MLX: window not created.", cub);
	else if (indic == 2)
		exit_clear("ERR_MLX: could not open the textures chosen in the map.",
			cub);
	else if (indic == 3)
		exit_clear("ERR_MLX: could not open the textures of the game : \
do not change the files without permission of an admin.", cub);
}
