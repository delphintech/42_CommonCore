/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:31:59 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/06 16:32:21 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	check_errors(int ac, char **av)
{
	int	fd;
	int	l;

	if (ac < 2)
		exit_clear("No argument given\n", NULL, NULL, NULL);
	if (ac > 2)
		exit_clear("Too many arguments\n", NULL, NULL, NULL);
	l = ft_strlen(av[1]);
	if (av[1][l - 1] != 'f' || av[1][l - 2] != 'd'
		|| av[1][l - 3] != 'f' || av[1][l - 4] != '.')
		exit_clear("Invalid map file\n", NULL, NULL, NULL);
	fd = open(av[1], O_RDONLY, 0777);
	if (fd < 0)
		exit_clear("No such file or directory\n", NULL, NULL, NULL);
	return (fd);
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	fd = check_errors(ac, av);
	file_to_map(fd, &(data.map));
	close(fd);
	fd = open(av[1], O_RDONLY, 0777);
	if (fd < 0)
		exit_clear("No such file or directory\n", NULL, NULL, NULL);
	data.map.origins = file_to_coord(fd);
	set_map_depth(&(data.map));
	set_map_color(&(data.map));
	close(fd);
	data.map.coords = make_2d_coords(&(data.map));
	set_map_limits(&(data.map));
	if (!data.map.coords)
		exit_clear("No coordinates\n", data.map.origins, NULL, NULL);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "Map");
	create_img(&data, &(data.map));
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 25, 25);
	mlx_loop_hook(data.mlx, no_event, &data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 3, close_button, &data);
	mlx_loop(data.mlx);
}
