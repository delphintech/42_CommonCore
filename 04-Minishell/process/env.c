/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:56 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 11:45:01 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	**empty_env(void)
{
	t_var	*new_var;
	t_var	**env_list;

	env_list = malloc(sizeof(t_var *));
	if (!env_list)
		return (NULL);
	*env_list = NULL;
	new_var = ft_new_var(ft_strdup("PWD"), getcwd(NULL, 0));
	var_add_back(env_list, new_var);
	new_var = ft_new_var(ft_strdup("_"), ft_strdup("/usr/bin/env"));
	var_add_back(env_list, new_var);
	return (env_list);
}

char	*get_env_value(t_var **env_list, char *name)
{
	t_var	*var;

	if (!name)
		return (NULL);
	var = find_var(env_list, name);
	if (!var)
		return (NULL);
	return (var->value);
}

t_var	**dup_env(char **envp)
{
	int		i;
	t_var	*new_var;
	t_var	**env_list;
	char	**line;

	if (!*envp)
		return (empty_env());
	env_list = malloc(sizeof(t_var *));
	if (!env_list)
		return (NULL);
	*env_list = NULL;
	i = 0;
	while (envp[i])
	{
		line = ft_split(envp[i], '=');
		new_var = ft_new_var(ft_strdup(line[0]), ft_strdup(line[1]));
		var_add_back(env_list, new_var);
		free_tab_char(line);
		i++;
	}
	return (env_list);
}

// char	**varlist_to_tab(t_var	**var_list)
// {
// 	int		i;
// 	char	*temp;
// 	t_var	*var;
// 	char	**tab;

// 	i = 0;
// 	var = *var_list;
// 	while (var)
// 	{
// 		i++;
// 		var = var->next;
// 	}
// 	tab = malloc((i + 1) * sizeof(char *));
// 	if (!tab)
// 		return (NULL);
// 	var = *var_list;
// 	i = 0;
// 	while (var)
// 	{
// 		temp = ft_strjoin(var->name, "=");
// 		tab[i++] = ft_strljoin(temp, var->value, ft_strlen(var->value));
// 		var = var->next;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }
