/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:07:11 by magahat           #+#    #+#             */
/*   Updated: 2024/11/20 17:58:25 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_clear(char *msg, t_cub *cub)
{
	if (cub)
		clear_cub(cub);
	if (ft_strncmp(msg, "", 1) == 0)
		exit (EXIT_FAILURE);
	else if (msg)
	{
		error_message(msg);
		exit (EXIT_FAILURE);
	}
	else
		exit (EXIT_SUCCESS);
}

void	error_handler(char *err)
{
	ft_putendl_fd("Error", 2);
	perror(err);
	exit (EXIT_FAILURE);
}

void	error_message(char *err)
{
	if (ft_strncmp(err, "", 1) != 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err, 2);
	}
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		exit_clear("ERR_INPUT: This program accept only one argument", NULL);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4))
		exit_clear("ERR_INPUT_MAP: must end by '.cub'", NULL);
	if (LENGTH < 960 || HEIGHT < 500)
		exit_clear("ERR_PROG: Window size is too small (960 x 500 minimum)",
			NULL);
	cub = parsing_map(argv[1]);
	gettimeofday(&cub->data.time, NULL);
	manage_game(cub);
}
