/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:03:32 by dabouab           #+#    #+#             */
/*   Updated: 2024/07/04 15:19:18 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "pipex.h"

char	**check_args_bonus(int ac, char **av, char **env);
void	run_commands(int ac, char **av, char **paths, char **env);
int		make_child(char *cmd, int fd_in, char **paths, char **env);

#endif
