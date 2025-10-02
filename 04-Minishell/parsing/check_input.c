/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:05:41 by magahat           #+#    #+#             */
/*   Updated: 2024/10/02 17:25:56 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	check_quotes(char *input)
{
	int	i;
	int	check;

	i = 0;
	while (input[i])
	{
		check = 1;
		if (is_quote(input[i]))
			check = go_end_quote(&input[i], input[i]);
		else if (ft_charcmp(input[i], "({["))
			check = go_end_quote(&input[i], input[i] + 1);
		else if (ft_charcmp(input[i], ")}]"))
			return (put_error(1, &input[i]), 0);
		if (!check)
			return (put_error(3, &input[i]), 0);
		else
			i += check;
	}
	return (1);
}

static int	check_special_characters(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
			i += go_end_quote(&input[i], input[i]);
		else if (input[i] != 92 && !ft_charcmp(input[i], "(){}[];!:*&,"))
			i++;
		else
			return (put_error(1, &input[i]), 0);
	}
	return (1);
}

static int	check_redirections(char *input, int redir, int i)
{
	while (input[i])
	{
		if (ft_charcmp(input[i], "><") && (!correct_format_redir(&input[i])
				|| redir == 1))
			return (put_error(4, "><"), 0);
		else if (ft_charcmp(input[i], "><"))
		{
			i += correct_format_redir(&input[i]);
			redir = 1;
		}
		else if (ft_isspace(input[i]))
			i++;
		else
		{
			if (is_quote(input[i]))
				i += go_end_quote(&input[i], input[i]);
			else
				i++;
			redir = 0;
		}
	}
	if (redir == 1)
		return (put_error(4, "><"), 0);
	return (1);
}

static int	check_pipes(char *input, int tube, int i)
{
	while (input[i])
	{
		if (input[i] == '|' && (tube == 1 || tube == 2))
			return (0);
		else if (input[i] == '|')
		{
			tube = 1;
			i++;
		}
		else if (ft_charcmp(input[i], "><"))
			i += correct_format_redir(&input[i]);
		else if (ft_isspace(input[i]))
			i++;
		else
		{
			if (is_quote(input[i]))
				i += go_end_quote(&input[i], input[i]);
			else
				i++;
			tube = 0;
		}
	}
	if (tube == 1)
		return (0);
	return (1);
}

int	check_input(t_params *params)
{
	if (!check_quotes(params->input))
		return (params->err_code = 2, 0);
	if (!check_redirections(params->input, 0, 0))
		return (params->err_code = 2, 0);
	if (!check_pipes(params->input, 2, 0))
		return (put_error(2, NULL), params->err_code = 2, 0);
	if (!check_special_characters(params->input))
		return (params->err_code = 2, 0);
	return (1);
}
