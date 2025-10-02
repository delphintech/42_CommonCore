/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:09:35 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 11:44:13 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "struct.h"
# include "define.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

void	exit_clear(char *msg, t_cub *cub);
void	error_message(char *err);
void	error_handler(char *err);

/***** PARSING *****/
// parsing
char	*fill_width(char *str, int width, char c);
t_cub	*parsing_map(char *argv);

// parsing utils
char	*fill_parsing(char **words, char *params);
int		is_allspaces(char *str);
int		ft_access(char *path, int oflag);
char	*gnl_no_eol(int fd);
void	clear_cub(t_cub *cub);

// checks
int		check_params(t_cub *cub, int *is_map, int fd);
void	check_map(t_cub *cub);

// tabs_utils
int		table_size(char	**tab);
char	**tab_add(char **tab, char *str);
void	clear_tab(char **tab);
void	clear_tab_line(char **tab, char *line);
int		check_tab_char(char **tab, int size, char *set);

/***** VISUAL *****/
int		manage_visual(t_cub *cub);
void	raycasting(t_cub *cub);
void	draw_map(int col, t_cub *cub, int start, int end);
void	close_sprite(t_cub *cub);
void	open_textures(t_cub *cub);
void	close_textures(t_cub *cub);

/***** GAME *****/
void	manage_game(t_cub *cub);
void	move_a(t_cub *cub);
void	move_d(t_cub *cub);
void	move_w(t_cub *cub);
void	move_s(t_cub *cub);
void	change_orientation(t_cub *cub, int indic);
void	start_orientation(t_cub *cub);
void	exit_game(t_cub *cub, char *msg);
int		mouse_orientation(int x, int y, t_cub *cub);
int		end_game(t_cub *cub);
void	exit_fail(t_cub *cub, int indic);

/***** BONUS *****/
// minimap
void	minimap(t_cub *cub);
void	put_player(t_cub *cub);
void	draw_minimap(char **centered, t_cub *cub);

//door
void	check_map_doors(t_cub *cub);
void	open_door(t_cub *cub);

#endif