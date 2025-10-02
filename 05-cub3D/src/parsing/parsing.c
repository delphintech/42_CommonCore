/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:38:56 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 11:46:40 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		exit_clear("ERR_MEM: memory not allocated.\n", NULL);
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
	cub->ceiling = -1;
	cub->floor = -1;
	cub->player_x = -1;
	cub->player_y = -1;
	cub->mini_y = HEIGHT - 80 - MINI_SIZE / 2;
	cub->mini_x = 50 + MINI_SIZE / 2;
	cub->orientation = 0;
	cub->height = 0;
	cub->width = 0;
	cub->map = malloc(sizeof(char *));
	if (!cub->map)
		exit_clear("ERR_MEM: memory not allocated.\n", cub);
	*cub->map = NULL;
	return (cub);
}

char	*fill_width(char *str, int width, char c)
{
	int		i;
	char	*new_str;

	if ((int)ft_strlen(str) == width)
		return (str);
	new_str = malloc((width + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (i < width)
	{
		new_str[i] = c;
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

static int	set_color(char *str, int *params)
{
	int		color;
	int		rgb[3];
	char	**tab;

	if (*params > 0)
		return (-1);
	tab = ft_split(str, ',');
	if (table_size(tab) != 3
		|| check_tab_char(tab, 3, "0123456789,") == FALSE)
		return (clear_tab(tab), -1);
	rgb[0] = ft_atoi(tab[0]);
	rgb[1] = ft_atoi(tab[1]);
	rgb[2] = ft_atoi(tab[2]);
	clear_tab(tab);
	if ((rgb[0] < 0 || rgb[0] > 255) || (rgb[1] < 0 || rgb[1] > 255)
		|| (rgb[2] < 0 || rgb[2] > 255))
		return (-1);
	color = rgb[0] << 16;
	color += rgb[1] << 8;
	color += rgb[2];
	return (color);
}

static void	get_params(t_cub *cub, char *line, int *is_map, int fd)
{
	char	**words;
	int		tab_size;

	words = ft_split(line, ' ');
	if (!words || !*words)
		return (clear_tab(words));
	tab_size = table_size(words);
	if (tab_size == 2 && ft_strncmp(words[0], "NO", 3) == 0)
		cub->north = fill_parsing(words, cub->north);
	else if (tab_size == 2 && ft_strncmp(words[0], "SO", 3) == 0)
		cub->south = fill_parsing(words, cub->south);
	else if (tab_size == 2 && ft_strncmp(words[0], "WE", 3) == 0)
		cub->west = fill_parsing(words, cub->west);
	else if (tab_size == 2 && ft_strncmp(words[0], "EA", 3) == 0)
		cub->east = fill_parsing(words, cub->east);
	else if (tab_size == 2 && ft_strncmp(words[0], "F", 2) == 0)
		cub->floor = set_color(words[1], &cub->floor);
	else if (tab_size == 2 && ft_strncmp(words[0], "C", 2) == 0)
		cub->ceiling = set_color(words[1], &cub->ceiling);
	else if (check_params(cub, is_map, fd) == FALSE)
	{
		clear_tab_line(words, line);
		exit_clear("", cub);
	}
	clear_tab(words);
}

t_cub	*parsing_map(char *argv)
{
	int		fd;
	int		is_map;
	char	*line;
	t_cub	*cub;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit_clear("ERR_INPUT: no such file or directory.", NULL);
	cub = init_cub();
	line = NULL;
	is_map = FALSE;
	while (1)
	{
		free(line);
		line = gnl_no_eol(fd);
		if (!line)
			break ;
		if (is_map == FALSE)
			get_params(cub, line, &is_map, fd);
		if (is_map == TRUE)
			cub->map = tab_add(cub->map, line);
	}
	close (fd);
	check_map(cub);
	return (cub);
}
