/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:24 by magahat           #+#    #+#             */
/*   Updated: 2024/10/09 15:51:54 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	manage_input(t_parsing **parsing, t_params *params)
{
	t_parsing	*temp;

	temp = *parsing;
	while (temp)
	{
		if (!manage_redir(temp))
			return (0);
		manage_cmd_arg(temp);
		manage_quotes(temp, params);
		free(temp->input);
		temp = temp->next;
	}
	return (1);
}

static int	count_nb_cmd(char *input)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (input[i])
	{
		if (is_quote(input[i]))
			i += go_end_quote(&input[i], input[i]);
		else if (input[i] == '|')
		{
			nb++;
			i++;
		}
		else
			i++;
	}
	if (go_end_spaces(input) == i)
		return (0);
	return (nb);
}

t_parsing	*manage_parsing(t_params *params)
{
	t_parsing	*parsing;

	if (!check_input(params))
		return (free(params->input), NULL);
	params->nb_cmd = count_nb_cmd(params->input);
	if (!params->nb_cmd)
		return (free(params->input), NULL);
	split_with_pipes(params, 0, 0);
	free(params->input);
	if (!params->cmd_input)
		return (NULL);
	parsing = init_parsing(params);
	if (!parsing)
		return (free_tab_char(params->cmd_input), NULL);
	manage_input(&parsing, params);
	return (parsing);
}
