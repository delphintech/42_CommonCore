/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:32:02 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/02 12:14:42 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "./minilibx/mlx.h"

# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define WIN_H	600
# define WIN_W	900
# define IMG_H	(WIN_H - 50)
# define IMG_W	(WIN_W - 50)

typedef struct s_line
{
	float	dx;
	float	dy;
	float	new_x;
	float	new_y;
	int		new_color;
	int		grad_red;
	int		grad_green;
	int		grad_blue;
}	t_line;

typedef struct s_coord
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_coord	*next;
}	t_coord;

typedef struct s_map
{
	int		heigth;
	int		width;
	int		max_x;
	int		max_y;
	int		min_z;
	int		max_z;
	t_coord	**origins;
	t_coord	**coords;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		pixel_bits;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	image;
	t_map	map;
}	t_data;

// coords.c
t_coord		**file_to_coord(int fd);
t_coord		**make_2d_coords(t_map *map);
void		scale(t_coord **coords, float size, int off_x, int off_y);

// draw.c
void		put_pixel(t_img *img, int x, int y, int color);
void		draw_line(t_img *img, t_coord *start, t_coord *end);
void		scale_to_image(t_map *map, int height, int width);
void		create_img(t_data *data, t_map *map);

// events.c
void		free_char(char *str, char **tab);
void		exit_clear(char *msg, t_coord **coords, char *str, char **tab);
int			handle_key(int keycode, t_data *data);
int			no_event(void *data);
int			close_button(t_data *data);

// struct.c
t_coord		*new_coord(int x, int y, int z, int color);
void		coord_add_back(t_coord **coords, t_coord *new);
int			find_min_x(t_coord **coords);
int			find_min_y(t_coord **coords);
t_coord		*find_front(t_coord *coord, int line_size);

// utils.c
int			ft_atoi_base(char *str, char *base);

// color.c
void		set_map_color(t_map *map);
void		set_next_point_color(t_line *line);
void		set_color_grad(t_line *line, t_coord *start, t_coord *end);

// map.c
void		set_map_depth(t_map *map);
void		set_map_limits(t_map *map);
void		file_to_map(int fd, t_map *map);

// events_bonus.c
void		zoom(int keycode, t_data *data);
void		translate(int keycode, t_data *data);
void		depth_change(int keycode, t_data *data);
void		rotate(t_data *data);
void		cabinet_projection(t_data *data);

#endif
