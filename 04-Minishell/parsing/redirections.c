/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:49 by magahat           #+#    #+#             */
/*   Updated: 2024/10/01 15:33:46 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	name_redir_in(t_parsing *data, char *input, int nb)
{
	int	i;
	int	l;

	i = 0;
	if (input[i + 1] == '<')
		data->type_redir_in[nb] = 1;
	i += correct_format_redir(&input[i]);
	i += go_end_spaces(&input[i]);
	l = 0;
	while (input[i + l] && !ft_isspace(input[i + l])
		&& !ft_charcmp(input[i + l], "<>|"))
	{
		if (is_quote(input[i + l]))
			l += go_end_quote(&input[i + l], input[i + l]);
		else
			l++;
	}
	data->redir_in[nb] = ft_substr(input, i, l);
	return (i + l);
}

static int	name_redir_out(t_parsing *data, char *input, int nb)
{
	int	i;
	int	l;

	i = 0;
	if (input[i + 1] == '>')
		data->type_redir_out[nb] = 1;
	i += correct_format_redir(&input[i]);
	i += go_end_spaces(&input[i]);
	l = 0;
	while (input[i + l] && !ft_isspace(input[i + l])
		&& !ft_charcmp(input[i + l], "<>|"))
	{
		if (is_quote(input[i + l]))
			l += go_end_quote(&input[i + l], input[i + l]);
		else
			l++;
	}
	data->redir_out[nb] = ft_substr(input, i, l);
	return (i + l);
}

static void	fill_redir(t_parsing *data, int in, int out)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (is_quote(data->input[i]))
			i += go_end_quote(&data->input[i], data->input[i]);
		else if (data->input[i] == '<')
		{
			i += name_redir_in(data, &data->input[i], in);
			in++;
			data->redir_in[in] = NULL;
		}
		else if (data->input[i] == '>')
		{
			i += name_redir_out(data, &data->input[i], out);
			out++;
			data->redir_out[out] = NULL;
		}
		else
			i++;
	}
}

int	manage_redir(t_parsing *data)
{
	count_redirections(data);
	if (data->nb_redir_in < 1 && data->nb_redir_out < 1)
		return (1);
	if (data->nb_redir_in > 0)
	{
		data->type_redir_in = put_zero_array(data->nb_redir_in);
		data->redir_in = malloc(sizeof(char *) * (data->nb_redir_in + 1));
		if (!data->redir_in)
			return (ft_printf_fd(2, "ERR_MALLOC\n"), 0);
	}
	if (data->nb_redir_out > 0)
	{
		data->type_redir_out = put_zero_array(data->nb_redir_out);
		data->redir_out = malloc(sizeof(char *) * (data->nb_redir_out + 1));
		if (!data->redir_out)
			return (ft_printf_fd(2, "ERR_MALLOC\n"), 0);
	}
	fill_redir(data, 0, 0);
	return (1);
}
