/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:00:59 by dabouab           #+#    #+#             */
/*   Updated: 2024/07/04 15:16:07 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

void	exit_clear(char *msg, char **tab);
char	**get_paths(char **env);
char	**check_args(int ac, char **av, char **env);
void	exec_cmd(char **cmd, char **paths, char **env);

#endif
