/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:40:15 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/06 16:32:42 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_char(char *str, char **tab)
{
	int	i;

	if (str)
		free(str);
	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	exit_clear(char *msg, t_coord **coords, char *str, char **tab)
{
	t_coord	*temp;
	int		i;

	if (str || tab)
		free_char(str, tab);
	if (coords)
	{
		while (*coords)
		{
			temp = (*coords)->next;
			free(*coords);
			*coords = temp;
		}
		free(coords);
	}
	if (msg)
	{
		i = 0;
		while (msg[i])
			i++;
		write(2, msg, i);
		exit(EXIT_FAILURE);
	}
}

int	no_event(void *data)
{
	(void)data;
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_button(data);
	if (keycode == XK_i || keycode == XK_o)
		zoom(keycode, data);
	if (keycode == XK_Up || keycode == XK_Down
		|| keycode == XK_Left || keycode == XK_Right)
		translate(keycode, data);
	if (keycode == XK_h || keycode == XK_l)
		depth_change(keycode, data);
	if (keycode == XK_r)
		rotate(data);
	if (keycode == XK_p)
		cabinet_projection(data);
	return (0);
}

int	close_button(t_data *data)
{
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit_clear(NULL, data->map.origins, NULL, NULL);
	exit_clear(NULL, data->map.coords, NULL, NULL);
	exit(EXIT_SUCCESS);
}
