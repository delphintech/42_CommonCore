/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:18:15 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/19 16:36:33 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**center_player(t_cub *cub, char **new_map, int i, int delta_x)
{
	int	j;
	int	delta_y;

	while (i < 24)
	{
		new_map[i] = malloc(25 * sizeof(char));
		if (!new_map[i])
			return (clear_tab(new_map), NULL);
		j = 0;
		delta_y = cub->player_y - 12;
		while (j < 24)
		{
			if (delta_x >= 0 && delta_x < cub->height
				&& delta_y >= 0 && delta_y < cub->width)
				new_map[i][j] = cub->map[delta_x][delta_y];
			else
				new_map[i][j] = ' ';
			delta_y++;
			j++;
		}
		new_map[i++][j] = '\0';
		delta_x++;
	}
	new_map[i] = NULL;
	return (new_map);
}

void	minimap(t_cub *cub)
{
	int		i;
	int		delta_x;
	char	**centered;

	centered = malloc(25 * sizeof(char *));
	if (!centered)
		exit_game(cub, "ERR_MEM: memory not allocated.\n");
	i = 0;
	delta_x = cub->player_x - 12;
	if (!center_player(cub, centered, i, delta_x))
		exit_game(cub, "ERR_MEM: memory not allocated.\n");
	draw_minimap(centered, cub);
}
