/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:55:58 by magahat           #+#    #+#             */
/*   Updated: 2024/10/10 11:49:50 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../structs.h"

// Function_utils
char		*ft_strljoin(char *s1, char *s2, unsigned int length);
char		*ft_strbchr(char *str, char c);
long long	ft_atoi_long(const char *nptr);
int			ft_is_valid_num(char *str);
char		*remove_index(char *str, int index, char c);

// Program_utils
void		handler(int signom);
void		child_handler(int signom);
int			ft_error(t_params *params, int error_code, char *msg, char *cmd);
// void		clean_tab(char **tab, int size);
void		exit_clear(char *msg, int err_code,
				t_params *params, t_parsing *cmd_list);
void		wait_children(t_params *params);

// utils_pour_test
void		ft_puttab_fd(char **tab, int fd);
void		ft_putar_fd(int *arr, int fd, int nb);
void		print_structure(t_parsing **parsing, t_params *params);
void		print_parsing(t_parsing *parsing, t_params *params);

// utils free
void		free_tab_char(char **tab);
char		*str_join_replace(char *s1, char *s2);
void		clear_parsing_list(t_parsing *parsing);
char		*free_null(char *str);

#endif
