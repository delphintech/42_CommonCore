/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:04:13 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 10:59:12 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/* base */
# define TRUE	1
# define FALSE	0

/* Window size and size utils */
# define LENGTH 1920
# define HEIGHT	1000
# define MINI_SIZE 192
# define TEX_H 64
# define TEX_W 48

/* Field Of View: plus il est grand plus on vois sur les cotes */
/* plus il est petit, plus notre champ de vision est ressere */
# define FOV 1.5

/* Textures path for game to work */
# define DOOR_PATH "./assets/utils/door.xpm"
# define PLAYER_N "./assets/utils/player_N.xpm"
# define PLAYER_S "./assets/utils/player_S.xpm"
# define PLAYER_E "./assets/utils/player_E.xpm"
# define PLAYER_W "./assets/utils/player_W.xpm"
# define TORCH_1 "./assets/utils/torch_1.xpm"
# define TORCH_2 "./assets/utils/torch_2.xpm"
# define TORCH_3 "./assets/utils/torch_3.xpm"
# define TORCH_4 "./assets/utils/torch_4.xpm"
# define TORCH_5 "./assets/utils/torch_5.xpm"
# define CURSOR_PATH "./assets/utils/cursor.xpm"

/* To activate mouse mouvement = 1 */
# define MOUSE 0

#endif