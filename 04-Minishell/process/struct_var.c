/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:19:07 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/07 15:03:22 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*ft_new_var(char *name, char *value)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	var_add_back(t_var	**var_list, t_var *new)
{
	t_var	*last;

	if (!new || !var_list)
		return ;
	if (!*var_list)
	{
		*var_list = new;
		return ;
	}
	last = *var_list;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	del_var(t_var **var_list, t_var	*var)
{
	t_var	*temp;

	if (!var_list || !*var_list || !var)
		return ;
	temp = *var_list;
	while (temp)
	{
		if (temp == var)
		{
			if (temp->prev)
				temp->prev->next = temp->next;
			else
				*var_list = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			free(temp->name);
			if (temp->value)
				free(temp->value);
			free(temp);
			break ;
		}
		temp = temp->next;
	}
}

void	clear_var_list(t_var **var_list)
{
	t_var	*temp;

	if (!var_list)
		return ;
	temp = *var_list;
	while (temp)
	{
		temp = (*var_list)->next;
		free((*var_list)->name);
		if ((*var_list)->value)
			free((*var_list)->value);
		free(*var_list);
		*var_list = temp;
	}
	free(var_list);
}

t_var	*find_var(t_var	**var_list, char *name)
{
	int		length;
	t_var	*temp;

	length = ft_strlen(name);
	temp = *var_list;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, length + 1) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
