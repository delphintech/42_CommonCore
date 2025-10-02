/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:33:34 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/24 14:13:49 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	ft_fill(char *d, char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*s;
	char	*d;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (d <= s)
		ft_fill(d, s, n);
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	dest = d;
	return (dest);
}
