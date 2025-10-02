/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_arg_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:23 by magahat           #+#    #+#             */
/*   Updated: 2024/10/01 16:53:31 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_without_redir(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i + len])
	{
		if (is_quote(input[i + len]))
			len += go_end_quote(&input[i + len], input[i + len]);
		else if (ft_charcmp(input[i + len], "><"))
			i += go_end_redir(&input[i + len]);
		else
			len++;
	}
	return (len);
}

static char	*extract_entire_quote(char *input, char quote)
{
	int		i;
	int		j;
	char	*output;

	i = 1;
	while (input[i] && input[i] != quote)
		i++;
	output = malloc(sizeof(char) * (i + 2));
	if (!output)
		return (NULL);
	j = 0;
	while (j < i + 1)
	{
		output[j] = input[j];
		j++;
	}
	output[j] = '\0';
	return (output);
}

char	*trim_redir(char *input, int i, int k)
{
	char	*output;
	char	*tmp;
	int		j;

	output = ft_calloc(sizeof(char), len_without_redir(input) + 1);
	if (!output)
		return (NULL);
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			tmp = extract_entire_quote(&input[i], input[i]);
			j = 0;
			while (tmp[j])
				output[k++] = tmp[j++];
			i += go_end_quote(&input[i], input[i]);
			free(tmp);
		}
		else if (ft_charcmp(input[i], "<>"))
			i += go_end_redir(&input[i]);
		else
			output[k++] = input[i++];
	}
	output[k] = '\0';
	return (output);
}
