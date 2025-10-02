/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:19 by magahat           #+#    #+#             */
/*   Updated: 2024/10/01 15:41:05 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_next_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '|')
	{
		if (is_quote(input[i]))
			i += go_end_quote(&input[i], input[i]);
		else
			i++;
	}
	i--;
	while (i >= 0 && ft_isspace(input[i]))
		i--;
	return (i + 1);
}

static int	jump_spaces_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (ft_isspace(input[i]) || input[i] == '|'))
		i++;
	return (i);
}

int	split_with_pipes(t_params *params, int i, int j)
{
	int	len_cmd;
	int	len;

	params->cmd_input = malloc(sizeof(char *) * (params->nb_cmd + 1));
	if (!params->cmd_input)
		return (ft_printf_fd(2, "ERR_MALLOC\n"), 0);
	while (params->input[i] && j < params->nb_cmd)
	{
		i += jump_spaces_pipes(&params->input[i]);
		len_cmd = find_next_pipe(&params->input[i]);
		params->cmd_input[j] = malloc(sizeof(char) * len_cmd + 1);
		if (!params->cmd_input[j])
			return (ft_printf_fd(2, "ERR_MALLOC\n"), 0);
		len = 0;
		while (params->input[i] && len < len_cmd)
		{
			params->cmd_input[j][len] = params->input[i];
			i++;
			len++;
		}
		params->cmd_input[j][len] = '\0';
		j++;
	}
	params->cmd_input[j] = NULL;
	return (1);
}
