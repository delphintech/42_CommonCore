/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:35:16 by magahat           #+#    #+#             */
/*   Updated: 2024/10/09 15:05:00 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	var_name = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[0] == '?')
			return (free(var_name), ft_strdup("?"));
		else if (ft_isdigit(str[0]))
			return (free(var_name), ft_strdup("0"));
		else if (ft_isalnum(str[i]) == 0)
			break ;
		var_name[i] = str[i];
		i++;
	}
	if (i == 0)
		return (free(var_name), NULL);
	var_name[i] = '\0';
	return (var_name);
}

static char	*get_value(t_params *params, char *name)
{
	t_var	*var;

	if (!name)
		return (ft_strdup("$"));
	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(params->err_code));
	if (ft_strncmp(name, "0", 2) == 0)
		return (NULL);
	var = find_var(params->env, name);
	if (var)
		return (ft_strdup(var->value));
	else
		return (NULL);
}

char	*var_expansion(t_params *params, char *str, int i, int start)
{
	char	*output;
	char	*var_name;
	char	*value;

	output = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			output = ft_strljoin(output, &str[start], i - start);
			var_name = get_var_name(&str[i + 1]);
			value = get_value(params, var_name);
			output = ft_strljoin(output, value, ft_strlen(value));
			start = i + ft_strlen(var_name) + 1;
			i = start - 1;
			free(var_name);
			free(value);
		}
		i++;
	}
	output = ft_strljoin(output, &str[start], i);
	return (free(str), output);
}
