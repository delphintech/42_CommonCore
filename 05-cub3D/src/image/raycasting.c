/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:19:36 by magahat           #+#    #+#             */
/*   Updated: 2024/11/12 14:52:48 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_ray	search_wall(t_cub *cub, t_ray ray)
{
	while (ray.hit == 0)
	{
		if (ray.sidedist_x < ray.sidedist_y)
		{
			ray.sidedist_x += ray.deltadist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.sidedist_y += ray.deltadist_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (cub->map[ray.map_x][ray.map_y] == '1')
			ray.hit = 1;
		else if (cub->map[ray.map_x][ray.map_y] == 'D')
			ray.hit = 2;
	}
	return (ray);
}

static t_ray	find_line_height(t_cub *cub, t_ray ray)
{
	if (ray.side == 0)
	{
		ray.perpwalldist = (ray.sidedist_x - ray.deltadist_x);
		ray.wall_x = cub->data.pl_y + ray.perpwalldist * ray.raydir_y;
	}
	else
	{
		ray.perpwalldist = (ray.sidedist_y - ray.deltadist_y);
		ray.wall_x = cub->data.pl_x + ray.perpwalldist * ray.raydir_x;
	}
	ray.wall_x -= floor(ray.wall_x);
	ray.tex_x = ray.wall_x * TEX_W;
	if ((ray.side == 0 && ray.raydir_x > 0)
		|| (ray.side == 1 && ray.raydir_y < 0))
		ray.tex_x = TEX_W - ray.tex_x - 1;
	ray.line_h = (int)(HEIGHT / ray.perpwalldist);
	ray.start_line = (-ray.line_h / 2 + HEIGHT / 2);
	if (ray.start_line < 0)
		ray.start_line = 0;
	ray.end_line = ray.line_h / 2 + HEIGHT / 2;
	if (ray.end_line >= HEIGHT || ray.perpwalldist == 0.000000)
		ray.end_line = HEIGHT - 1;
	ray.step = 1.0 * TEX_H / ray.line_h;
	return (ray);
}

static t_ray	step_ray(t_cub *cub, t_ray ray)
{
	if (ray.raydir_x < 0)
	{
		ray.step_x = -1;
		ray.sidedist_x = (cub->data.pl_x - ray.map_x) * ray.deltadist_x;
	}
	else
	{
		ray.step_x = 1;
		ray.sidedist_x = (ray.map_x + 1.0 - cub->data.pl_x) * ray.deltadist_x;
	}
	if (ray.raydir_y < 0)
	{
		ray.step_y = -1;
		ray.sidedist_y = (cub->data.pl_y - ray.map_y) * ray.deltadist_y;
	}
	else
	{
		ray.step_y = 1;
		ray.sidedist_y = (ray.map_y + 1.0 - cub->data.pl_y) * ray.deltadist_y;
	}
	return (ray);
}

static t_ray	init_ray(t_cub *cub, int col)
{
	t_ray	ray;

	if (col == LENGTH / 2)
		col--;
	ray.hit = 0;
	ray.map_x = (int)cub->data.pl_x;
	ray.map_y = (int)cub->data.pl_y;
	ray.camera_x = (2.0 * col) / LENGTH - 1;
	ray.raydir_x = cub->data.dir_x + cub->data.plane_x * ray.camera_x;
	ray.raydir_y = cub->data.dir_y + cub->data.plane_y * ray.camera_x;
	ray.deltadist_x = fabs(1 / ray.raydir_x);
	ray.deltadist_y = fabs(1 / ray.raydir_y);
	ray = step_ray(cub, ray);
	return (ray);
}

void	raycasting(t_cub *cub)
{
	t_ray	ray;
	int		col;

	col = 0;
	while (col < LENGTH)
	{
		ray = init_ray(cub, col);
		ray = search_wall(cub, ray);
		ray = find_line_height(cub, ray);
		cub->ray = ray;
		if (ray.end_line > ray.start_line)
			draw_map(col, cub, ray.start_line, ray.end_line);
		else
			draw_map(col, cub, ray.end_line, ray.start_line);
		col++;
	}
	cub->data.oldtime = cub->data.time;
	gettimeofday(&cub->data.time, NULL);
	cub->data.fps = ((cub->data.time.tv_sec
				- cub->data.oldtime.tv_sec) * 1000000
			+ (cub->data.time.tv_usec
				- cub->data.oldtime.tv_usec)) / 1000000.0;
	cub->data.rot_speed = cub->data.fps * 3.0;
	cub->data.move_speed = cub->data.fps * 5.0;
}
