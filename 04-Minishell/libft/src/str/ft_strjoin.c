/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:57:47 by magahat           #+#    #+#             */
/*   Updated: 2024/08/28 15:02:33 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		l1;
	int		l2;
	int		i;
	int		j;
	char	*str;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < l2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
