/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:40 by magahat           #+#    #+#             */
/*   Updated: 2024/10/09 15:15:02 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsing	*go_start_parsing(t_parsing *parsing)
{
	while (parsing && parsing->prev != NULL)
		parsing = parsing->prev;
	return (parsing);
}

static t_parsing	*goend_parsing(t_parsing *parsing)
{
	while (parsing && parsing->next != NULL)
		parsing = parsing->next;
	return (parsing);
}

static void	add_back_parsing(t_parsing **parsing, t_parsing *new)
{
	t_parsing	*end;

	if (!parsing || !new)
		return ;
	if (!(*parsing))
	{
		*parsing = new;
		return ;
	}
	end = goend_parsing(*parsing);
	end->next = new;
	new->prev = end;
}

static t_parsing	*new_parsing(char *input)
{
	t_parsing	*new;

	new = (t_parsing *)malloc(sizeof(t_parsing));
	if (!new)
		return (ft_printf_fd(2, "ERR_MALLOC\n"), NULL);
	new->input = ft_strdup(input);
	free(input);
	input = NULL;
	new->nb_redir_in = 0;
	new->nb_redir_out = 0;
	new->nb_arg = 0;
	new->type_redir_in = NULL;
	new->type_redir_out = NULL;
	new->redir_in = NULL;
	new->redir_out = NULL;
	new->cmd = NULL;
	new->arg = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_parsing	*init_parsing(t_params *params)
{
	int			i;
	t_parsing	*parsing;

	i = 1;
	parsing = new_parsing(params->cmd_input[0]);
	while (i < params->nb_cmd)
	{
		add_back_parsing(&parsing, new_parsing(params->cmd_input[i]));
		i++;
	}
	free(params->cmd_input);
	params->cmd_input = NULL;
	return (parsing);
}
