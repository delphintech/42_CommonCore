/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:21 by magahat           #+#    #+#             */
/*   Updated: 2024/10/02 17:24:27 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	go_end_quote(char *line, char quote)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] != quote)
		return (0);
	return (i + 1);
}

int	go_end_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
	{
		if (ft_isspace(input[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

int	*put_zero_array(int nb)
{
	int	*array;
	int	i;

	array = malloc(sizeof(int) * nb);
	if (!array)
		exit_clear("ERR_MALLOC\n", EXIT_FAILURE, NULL, NULL);
	i = 0;
	while (i < nb)
	{
		array[i] = 0;
		i++;
	}
	return (array);
}

void	put_error(int err, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == 1)
		ft_printf_fd(2, "syntax error near unexpected token `%c'\n", msg[0]);
	else if (err == 2)
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	else if (err == 3)
	{
		ft_putstr_fd("unexpected EOF while looking for matching ", 2);
		ft_printf_fd(2, "`%c'\n", msg[0]);
		ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
	}
	else if (err == 4)
		ft_printf_fd(2, "syntax error near unexpected token `%s'\n", msg);
}
