/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:54:21 by magahat           #+#    #+#             */
/*   Updated: 2024/10/03 12:02:32 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extract_name(char *input)
{
	int		i;

	i = 0;
	while (input[i] && !ft_isspace(input[i]))
	{
		if (is_quote(input[i]))
			i += go_end_quote(&input[i], input[i]);
		else
			i++;
	}
	if (i == 0)
		return (NULL);
	return (ft_substr(input, 0, i));
}

static int	count_nb_arg(char *input, int nb, int i)
{
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			i += go_end_quote(&input[i], input[i]);
			if (nb == 0)
				nb++;
		}
		else if (ft_isspace(input[i]))
		{
			i += go_end_spaces(&input[i]);
			nb++;
		}
		else if (nb == 0)
		{
			nb++;
			i++;
		}
		else
			i++;
	}
	if (nb != 0 && ft_isspace(input[i - 1]))
		nb--;
	return (nb);
}

static char	**name_arg(char *input, int nb_arg, int nb)
{
	int		i;
	char	**arg;

	arg = malloc(sizeof(char *) * (nb_arg + 1));
	if (!arg)
		return (NULL);
	i = 0;
	while (input[i] && nb < nb_arg)
	{
		i += go_end_spaces(&input[i]);
		arg[nb] = extract_name(&input[i]);
		i += ft_strlen(arg[nb]);
		nb++;
	}
	arg[nb] = NULL;
	return (arg);
}

void	manage_cmd_arg(t_parsing *data)
{
	int		i;
	char	*trimput;

	trimput = trim_redir(data->input, 0, 0);
	if (!trimput)
	{
		data->cmd = NULL;
		data->arg = NULL;
		return ;
	}
	i = go_end_spaces(trimput);
	data->cmd = extract_name(&trimput[i]);
	if (data->cmd)
	{
		i += ft_strlen(data->cmd);
		i += go_end_spaces(&trimput[i]);
		data->nb_arg = count_nb_arg(&trimput[i], 0, 0);
		if (data->nb_arg > 0)
			data->arg = name_arg(&trimput[i], data->nb_arg, 0);
		else
			data->arg = NULL;
	}
	free(trimput);
}
