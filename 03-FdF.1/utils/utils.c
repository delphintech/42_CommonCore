/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:18:00 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/01 17:39:13 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	find_index(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		l;
	int		result;

	i = 0;
	if (str[i] == '0')
		i++;
	if (ft_tolower(str[i]) == 'x')
		i++;
	l = ft_strlen(str) - i - 1;
	result = 0;
	while (l >= 0)
	{
		result += find_index(ft_tolower(str[i]), base)
			* pow(ft_strlen(base), l);
		i++;
		l--;
	}
	return (result);
}
