/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:27:27 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/30 15:33:11 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*newl;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		content = f(lst->content);
		newl = ft_lstnew(content);
		if (!newl)
		{
			del(content);
			ft_lstclear(&first, del);
			return (NULL);
		}
		ft_lstadd_back(&first, newl);
		lst = lst->next;
	}
	return (first);
}
