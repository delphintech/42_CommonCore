/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:25:29 by dabouab           #+#    #+#             */
/*   Updated: 2024/07/04 15:19:58 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	char	**paths;

	paths = check_args_bonus(ac, av, env);
	run_commands(ac, av, paths, env);
	exit_clear(NULL, paths);
	return (EXIT_SUCCESS);
}
