/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:28:53 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 10:25:25 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		pixel_bits;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_sprite {
	t_img	frames[6];
	int		width;
	int		height;
	int		delay;
	int		current_frame;
}		t_sprite;

typedef struct s_tex
{
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
	t_img		door;
	t_sprite	sprite;
	t_img		p_north;
	t_img		p_south;
	t_img		p_east;
	t_img		p_west;
	t_img		cursor;
}	t_tex;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			*map;
	t_tex			tex;
	double			pl_x;
	double			pl_y;
	double			dir_x;
	double			dir_y;
	double			dir_tmp;
	double			plane_x;
	double			plane_y;
	double			plane_tmp;
	struct timeval	time;
	struct timeval	oldtime;
	double			fps;
	double			rot_speed;
	double			move_speed;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	double	perpwalldist;
	double	wall_x;
	int		line_h;
	int		start_line;
	int		end_line;
	double	step;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
}	t_ray;

typedef struct s_cub
{
	int		player_x;
	int		player_y;
	int		mini_x;
	int		mini_y;
	char	orientation;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;
	int		width;
	int		height;
	char	**map;
	t_game	data;
	t_ray	ray;
}	t_cub;

#endif
