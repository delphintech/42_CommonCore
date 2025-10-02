/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:17:59 by magahat           #+#    #+#             */
/*   Updated: 2024/10/04 10:20:55 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_quotes(char *input)
{
	int		i;
	int		j;
	char	*quoted;

	i = 1;
	while (input[i] && input[i] != input[0])
		i++;
	quoted = malloc(sizeof(char) * (i));
	if (!quoted)
		return (NULL);
	j = 0;
	while (j < i - 1)
	{
		quoted[j] = input[j + 1];
		j++;
	}
	quoted[j] = '\0';
	return (quoted);
}

char	*extract_input(char *input)
{
	int		i;
	char	*output;

	i = 0;
	while (input[i] && !is_quote(input[i]))
		i++;
	output = malloc(sizeof(char) * (i + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (input[i] && !is_quote(input[i]))
	{
		output[i] = input[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
