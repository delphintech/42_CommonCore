/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:48:17 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 18:10:16 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "../structs.h"

// builtins_env
int		is_var_name_valid(char *name);
int		ft_export_var(t_params *params, char *name, char *value);
void	ft_export(t_params *params, t_parsing *cmd_data);
void	ft_unset(t_params *params, t_parsing *cmd_data);
void	ft_env(t_params *params, t_parsing *cmd_data);

// builtins_exec
int		env_builtins(t_params *params, t_parsing *cmd_data, int stdin_cpy);
int		is_builtins(t_parsing *cmd_data);
int		exec_builtins(t_params *params, t_parsing *cmd_data);
int		is_n_option(char *str);

// builtins
void	ft_echo(t_params *params, t_parsing *cmd_data);
void	ft_cd(t_params *params, t_parsing *cmd_data);
void	ft_pwd(t_params *params);
void	ft_exit(t_params *params, t_parsing *cmd_list, int stdin_copy);

// checks
int		get_infile(t_params *params, t_parsing *cmd_data);
int		get_outfile(t_params *params, t_parsing *cmd_data, int keep);
char	*get_path(t_params *params, t_parsing *cmd_data);
char	**path_in_args(t_parsing	*cmd_data, char	*path);

// env
t_var	**dup_env(char **envp);
char	*get_env_value(t_var **env_list, char *name);
// char	**varlist_to_tab(t_var	**var_list);

// heredoc
int		get_heredoc_input(char *limiter);
void	check_heredoc(t_parsing **cmd_list);

// process
char	*infile_path(t_params *params, t_parsing *cmd, int fd_in, int pfd[2]);
void	children(t_params *params, t_parsing *cmd_data, int fd_in, int pfd[2]);
int		make_child(t_params *params, t_parsing *cmd_data,
			int fd_in, int stdin_copy);
void	process(t_params *params, t_parsing **cmd_list);

// struc_var
t_var	*ft_new_var(char *name, char *value);
void	var_add_back(t_var	**var_list, t_var *new);
void	del_var(t_var **var_list, t_var	*var);
void	clear_var_list(t_var **var_list);
t_var	*find_var(t_var	**var_list, char *name);

#endif
