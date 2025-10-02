/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:58:08 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/14 14:40:37 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

t_rest	*ft_lstnew_gnl(int fd)
{
	t_rest	*new;

	new = (t_rest *)malloc(sizeof(t_rest));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->rest[0] = '\0';
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_gnl(t_rest **lst, t_rest *new)
{
	t_rest	*last;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}
