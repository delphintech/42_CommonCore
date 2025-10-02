/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:52:47 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/20 12:18:30 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_map_walls(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (i == 0 || i == cub->height - 1 || j == 0 || j == cub->width - 1)
			{
				if (ft_charcmp(cub->map[i][j], " 1") == 0)
					exit_clear("ERR_FILE: Map must be surrounded by walls",
						cub);
			}
			else if (ft_charcmp(cub->map[i][j], "0NSWED") > 0
				&& (ft_charcmp(cub->map[i + 1][j], " ") > 0
				|| ft_charcmp(cub->map[i - 1][j], " ") > 0
				|| ft_charcmp(cub->map[i][j + 1], " ") > 0
				|| ft_charcmp(cub->map[i][j - 1], " ") > 0))
				exit_clear("ERR_FILE: Map must be surrounded by walls", cub);
			j++;
		}
		i++;
	}
}

int	check_params(t_cub *cub, int *is_map, int fd)
{
	if (ft_access(cub->north, O_RDONLY) == FALSE
		|| ft_access(cub->south, O_RDONLY) == FALSE
		|| ft_access(cub->east, O_RDONLY) == FALSE
		|| ft_access(cub->west, O_RDONLY) == FALSE)
	{
		close(fd);
		return (error_message("ERR_FILE: Map texture parameters not valid"),
			FALSE);
	}
	if (ft_strncmp(ft_strrchr(cub->north, '.'), ".xpm", 4)
		|| ft_strncmp(ft_strrchr(cub->south, '.'), ".xpm", 4)
		|| ft_strncmp(ft_strrchr(cub->east, '.'), ".xpm", 4)
		|| ft_strncmp(ft_strrchr(cub->west, '.'), ".xpm", 4))
		return (error_message("ERR_FILE: Map texture files must end by '.xpm'"),
			FALSE);
	if (cub->floor < 0 || cub->ceiling < 0)
	{
		close(fd);
		return (error_message("ERR_FILE: Map color parameters not valid"),
			FALSE);
	}
	*is_map = TRUE;
	return (TRUE);
}

static void	check_map_chr(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (ft_charcmp(cub->map[i][j], "NSEW") == 1 && cub->player_x < 0)
			{
				cub->player_y = j;
				cub->player_x = i;
				cub->orientation = cub->map[i][j];
			}
			else if (ft_charcmp(cub->map[i][j], "NSEW") == 1
				&& cub->player_x > 0)
				exit_clear("ERR_FILE: multiple player positions", cub);
			else if (ft_charcmp(cub->map[i][j], " 01D") == 0)
				exit_clear("ERR_FILE: unautorized characters in the map", cub);
			j++;
		}
		i++;
	}
}

static void	set_map_dimensions(t_cub *cub)
{
	int	i;
	int	width;

	cub->height = table_size(cub->map);
	i = 0;
	width = 0;
	while (cub->map[i])
	{
		if ((int)ft_strlen(cub->map[i]) > width)
			width = ft_strlen(cub->map[i]);
		i++;
	}
	cub->width = width;
	i = 0;
	while (cub->map[i])
	{
		cub->map[i] = fill_width(cub->map[i], width, ' ');
		i++;
	}
}

void	check_map(t_cub *cub)
{
	int	i;

	set_map_dimensions(cub);
	if (cub->height == 0 || cub->width == 0)
		exit_clear("ERR_FILE: no map in file", cub);
	i = 0;
	while (cub->map[i])
		if (is_allspaces(cub->map[i++]) == TRUE)
			exit_clear("ERR_FILE: empty line inside the map", cub);
	check_map_chr(cub);
	if (cub->player_x < 0 || cub->player_y < 0)
		exit_clear("ERR_FILE: no player in the map", cub);
	cub->data.pl_x = cub->player_x + 0.5;
	cub->data.pl_y = cub->player_y + 0.5;
	check_map_walls(cub);
	check_map_doors(cub);
}
