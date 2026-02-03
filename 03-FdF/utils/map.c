/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:31:43 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/06 16:16:47 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_map_depth(t_map *map)
{
	t_coord	*temp;

	temp = *(map->origins);
	map->min_z = temp->z;
	map->max_z = temp->z;
	while (temp)
	{
		if (temp->z < map->min_z)
			map->min_z = temp->z;
		if (temp->z > map->max_z)
			map->max_z = temp->z;
		temp = temp->next;
	}
}

void	set_map_limits(t_map *map)
{
	t_coord	*temp;

	temp = *(map->coords);
	map->max_x = temp->x;
	map->max_y = temp->y;
	while (temp)
	{
		if (temp->x > map->max_x)
			map->max_x = temp->x;
		if (temp->y > map->max_y)
			map->max_y = temp->y;
		temp = temp->next;
	}
	scale_to_image(map, IMG_H, IMG_W);
}

void	file_to_map(int fd, t_map *map)
{
	int		x;
	int		y;
	char	*line;
	char	**z_tab;

	map->heigth = -1;
	map->width = -1;
	line = get_next_line(fd);
	y = 0;
	while (line)
	{
		x = 0;
		z_tab = ft_split(line, ' ');
		while (z_tab[x])
			x++;
		if (map->width != -1 && x != map->width)
			exit_clear("Not a rectangle !\n", NULL, line, z_tab);
		map->width = x;
		free_char(line, z_tab);
		line = get_next_line(fd);
		y++;
	}
	map->heigth = y;
	if (map->width == 0 || map->heigth == 0)
		exit_clear("Empty map\n", NULL, NULL, NULL);
}
