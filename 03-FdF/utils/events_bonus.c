/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:41:08 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/06 16:21:12 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	zoom(int keycode, t_data *data)
{
	float	zoom;

	if (keycode == XK_i)
		zoom = 1.2;
	if (keycode == XK_o)
		zoom = 0.8;
	mlx_destroy_image(data->mlx, data->image.img);
	scale(data->map.coords, zoom, 0, 0);
	create_img(data, &(data->map));
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 25, 25);
}

void	translate(int keycode, t_data *data)
{
	if (keycode == XK_Down)
		scale(data->map.coords, (float) 1, 0, 10);
	if (keycode == XK_Up)
		scale(data->map.coords, (float) 1, 0, -10);
	if (keycode == XK_Right)
		scale(data->map.coords, (float) 1, 10, 0);
	if (keycode == XK_Left)
		scale(data->map.coords, (float) 1, -10, 0);
	mlx_destroy_image(data->mlx, data->image.img);
	create_img(data, &(data->map));
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 25, 25);
}

void	depth_change(int keycode, t_data *data)
{
	float		coef;
	t_coord		*temp;

	mlx_destroy_image(data->mlx, data->image.img);
	if (keycode == XK_l)
		coef = 0.8;
	if (keycode == XK_h)
		coef = 1.2;
	temp = *(data->map.origins);
	while (temp)
	{
		temp->z = temp->z * coef;
		temp = temp->next;
	}
	set_map_depth(&(data->map));
	exit_clear(NULL, data->map.coords, NULL, NULL);
	data->map.coords = make_2d_coords(&(data->map));
	set_map_limits(&(data->map));
	set_map_color(&(data->map));
	create_img(data, &(data->map));
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 25, 25);
}

void	rotate(t_data *data)
{
	int			x;
	int			y;
	t_coord		*temp;

	mlx_destroy_image(data->mlx, data->image.img);
	temp = *(data->map.coords);
	while (temp)
	{
		x = temp->x;
		y = temp->y;
		temp->x = x * cosf(M_PI / (float) 12) + y * sinf(M_PI / (float) 12);
		temp->y = -x * sinf(M_PI / (float) 12) + y * cosf(M_PI / (float) 12);
		temp = temp->next;
	}
	scale(data->map.coords, 1, -find_min_x(data->map.coords),
		-find_min_y(data->map.coords));
	create_img(data, &(data->map));
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 25, 25);
}

void	cabinet_projection(t_data *data)
{
	t_coord		*temp_coord;
	t_coord		*temp_origin;

	mlx_destroy_image(data->mlx, data->image.img);
	temp_origin = *(data->map.origins);
	temp_coord = *(data->map.coords);
	while (temp_coord && temp_origin)
	{
		temp_coord->x = temp_origin->x + 0.5 * temp_origin->z * cosf(1.1065);
		temp_coord->y = temp_origin->y + 0.5 * temp_origin->z * sinf(1.1065);
		temp_coord = temp_coord->next;
		temp_origin = temp_origin->next;
	}
	scale(data->map.coords, 1, -find_min_x(data->map.coords),
		-find_min_y(data->map.coords));
	scale_to_image(&(data->map), IMG_H, IMG_W);
	create_img(data, &(data->map));
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 25, 25);
}
