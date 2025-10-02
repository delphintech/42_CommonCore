/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:55:38 by magahat           #+#    #+#             */
/*   Updated: 2024/10/04 10:34:46 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*char_quote_heredoc(char *input, char *output, int i)
{
	char	*extract;

	while (input[i])
	{
		if (input[i] == 39)
		{
			extract = extract_quotes(&input[i]);
			i += go_end_quote(&input[i], input[i]);
		}
		else if (input[i] == '"')
		{
			extract = extract_quotes(&input[i]);
			i += go_end_quote(&input[i], input[i]);
		}
		else
		{
			extract = extract_input(&input[i]);
			while (input[i] && !is_quote(input[i]))
				i++;
		}
		output = str_join_replace(output, extract);
	}
	return (free(input), output);
}

static char	*char_quote(char *input, t_params *params, char *output, int i)
{
	char	*extract;

	while (input[i])
	{
		if (input[i] == 39)
		{
			extract = extract_quotes(&input[i]);
			i += go_end_quote(&input[i], input[i]);
		}
		else if (input[i] == '"')
		{
			extract = var_expansion(params, extract_quotes(&input[i]), 0, 0);
			i += go_end_quote(&input[i], input[i]);
		}
		else
		{
			extract = var_expansion(params, extract_input(&input[i]), 0, 0);
			if (!ft_strncmp(extract, "$", 2) && is_quote(input[i + 1]))
				extract = free_null(extract);
			while (input[i] && !is_quote(input[i]))
				i++;
		}
		output = str_join_replace(output, extract);
	}
	return (free(input), output);
}

static char	**tab_quotes(char **input, int nb, t_params *params)
{
	int		i;

	if (nb == 0)
		return (input);
	i = 0;
	while (input[i])
	{
		input[i] = char_quote(input[i], params, NULL, 0);
		i++;
	}
	return (input);
}

void	manage_quotes(t_parsing *data, t_params *params)
{
	int	i;

	if (data->nb_redir_in > 0)
	{
		i = 0;
		while (i < data->nb_redir_in)
		{
			if (data->type_redir_in[i] == 0)
				data->redir_in[i] = char_quote(data->redir_in[i], params, \
				NULL, 0);
			else
				data->redir_in[i] = char_quote_heredoc(data->redir_in[i], \
				NULL, 0);
			i++;
		}
	}
	if (data->nb_redir_out > 0)
		data->redir_out = tab_quotes(data->redir_out, data->nb_redir_out, \
		params);
	if (data->nb_arg > 0)
		data->arg = tab_quotes(data->arg, data->nb_arg, params);
	if (data->cmd)
		data->cmd = char_quote(data->cmd, params, NULL, 0);
}
