/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:19:56 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/20 09:44:48 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_map_doors(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'D'
				&& ((cub->map[i + 1][j] == '1' && cub->map[i - 1][j] == '1')
				|| (cub->map[i][j + 1] == '1' && cub->map[i][j - 1] == '1')))
				j++;
			else if (cub->map[i][j] != 'D')
				j++;
			else
				exit_clear("ERR_FILE: Doors must be surrounded by walls", cub);
		}
		i++;
	}
}

void	open_door(t_cub *cub)
{
	int	x;
	int	y;

	x = cub->player_x;
	y = cub->player_y;
	if (cub->orientation == 'N' && cub->map[x - 1][y] == 'D')
		cub->map[x - 1][y] = '0';
	else if (cub->orientation == 'S' && cub->map[x + 1][y] == 'D')
		cub->map[x + 1][y] = '0';
	else if (cub->orientation == 'W' && cub->map[x][y - 1] == 'D')
		cub->map[x][y - 1] = '0';
	else if (cub->orientation == 'E' && cub->map[x][y + 1] == 'D')
		cub->map[x][y + 1] = '0';
}
