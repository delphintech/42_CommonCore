/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:30 by magahat           #+#    #+#             */
/*   Updated: 2024/10/09 15:15:21 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../structs.h"

/* PARSING */
t_parsing	*manage_parsing(t_params *params);
int			check_input(t_params *params);
int			split_with_pipes(t_params *params, int i, int j);
int			manage_redir(t_parsing *parsing);
void		manage_cmd_arg(t_parsing *data);

/* STRUCTURE PARSING */
t_parsing	*init_parsing(t_params *params);
t_parsing	*go_start_parsing(t_parsing *parsing);

/* REDIRECTIONS */
void		count_redirections(t_parsing *parsing);
int			correct_format_redir(char *input);
int			go_end_redir(char *input);
char		*trim_redir(char *input, int i, int k);

/* QUOTES */
void		manage_quotes(t_parsing *data, t_params *params);
char		*extract_quotes(char *input);
char		*extract_input(char *input);

/* UTILS */
int			is_quote(char c);
int			go_end_quote(char *line, char quote);
int			go_end_spaces(char *input);
int			correct_format_redir(char *input);
int			*put_zero_array(int nb);
char		*str_join_replace(char *s1, char *s2);
void		put_error(int err, char *msg);

/* EXPANSION */
char		*var_expansion(t_params *params, char *str, int i, int start);

#endif
