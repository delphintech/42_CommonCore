/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pour_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:19:39 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/09 15:44:42 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_structure(t_parsing **parsing, t_params *params)
{
	t_parsing	*temp;

	temp = *parsing;
	while (temp)
	{
		print_parsing(temp, params);
		temp = temp->next;
	}
}

void	print_parsing(t_parsing *parsing, t_params *params)
{
	(void)params;
	if (parsing->nb_redir_in > 0)
	{
		ft_putendl_fd("------- infiles -------", 1);
		ft_puttab_fd(parsing->redir_in, 1);
		ft_putar_fd(parsing->type_redir_in, 1, parsing->nb_redir_in);
	}
	if (parsing->nb_redir_out > 0)
	{
		ft_putendl_fd("------- outfiles -------", 1);
		ft_puttab_fd(parsing->redir_out, 1);
		ft_putar_fd(parsing->type_redir_out, 1, parsing->nb_redir_out);
	}
	if (parsing->cmd)
	{
		ft_printf_fd(1, "cmd = -%s-\n", parsing->cmd);
	}
	if (parsing->nb_arg > 0)
	{
		ft_putendl_fd("------- arg -------", 1);
		ft_printf_fd(1, "nb_arg = %i\n", parsing->nb_arg);
		ft_puttab_fd(parsing->arg, 1);
	}
	ft_putendl_fd("------------------", 1);
}

void	ft_puttab_fd(char **tab, int fd)
{
	while (*tab)
	{
		ft_putstr_fd(*tab, fd);
		ft_putstr_fd("\n", fd);
		tab++;
	}
}

void	ft_putar_fd(int *arr, int fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		ft_putnbr_fd(arr[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}
