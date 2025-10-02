/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:29:37 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/06 16:20:37 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	line_to_coord(t_coord **origins, int y, char *z_line)
{
	int			x;
	t_coord		*new;
	char		**z_tab;
	char		**z_data;

	z_tab = ft_split(z_line, ' ');
	x = 0;
	while (z_tab[x])
	{
		z_data = ft_split(z_tab[x], ',');
		if (z_data[1])
			new = new_coord(x * 100, y * 100, ft_atoi(z_data[0]) * 10,
					ft_atoi_base(z_data[1], "0123456789abcdef"));
		else
			new = new_coord(x * 100, y * 100, ft_atoi(z_data[0]) * 10,
					0xffffff);
		coord_add_back(origins, new);
		free_char(NULL, z_data);
		x++;
	}
	free_char(NULL, z_tab);
}

t_coord	**file_to_coord(int fd)
{
	int			y;
	char		*line;
	t_coord		**origins;

	origins = malloc(sizeof(t_coord *));
	if (!origins)
		exit_clear("Malloc failure.\n", NULL, NULL, NULL);
	*origins = NULL;
	line = get_next_line(fd);
	y = 0;
	while (line)
	{
		line_to_coord(origins, y, line);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	return (origins);
}

t_coord	**make_2d_coords(t_map *map)
{
	int			xyz[3];
	t_coord		*new;
	t_coord		*temp;
	t_coord		**coords;

	if (!(map->origins))
		exit_clear("No coordinates\n", NULL, NULL, NULL);
	coords = malloc(sizeof(t_coord *));
	if (!coords)
		exit_clear("Malloc failure.\n", NULL, NULL, NULL);
	*coords = NULL;
	temp = *(map->origins);
	while (temp)
	{
		xyz[0] = (temp->x - temp->y) * cosf(M_PI / (float) 6);
		xyz[1] = (temp->x + temp->y) * sinf(M_PI / (float) 6) - temp->z;
		xyz[2] = temp->z;
		new = new_coord(xyz[0], xyz[1], xyz[2], temp->color);
		coord_add_back(coords, new);
		temp = temp->next;
	}
	scale(coords, 1, -find_min_x(coords), -find_min_y(coords));
	return (coords);
}

void	scale(t_coord **coords, float size, int off_x, int off_y)
{
	t_coord		*temp;

	temp = *coords;
	while (temp)
	{
		temp->x = temp->x + off_x;
		temp->y = temp->y + off_y;
		temp = temp->next;
	}
	temp = *coords;
	while (temp)
	{
		temp->x = round(temp->x * size);
		temp->y = round(temp->y * size);
		temp = temp->next;
	}
}
