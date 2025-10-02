/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:08:47 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/10 16:29:23 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// // Remplace s1 qui est free par s1 + (s2 jusqu'à length)
char	*ft_strljoin(char *s1, char *s2, unsigned int length)
{
	unsigned int		i;
	unsigned int		j;
	char				*str;

	if (length <= ft_strlen(s2))
		str = malloc(sizeof(char) * (ft_strlen(s1) + length + 1));
	else
		str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && j < length)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

// Returns the first part of str until first occurence of c (included)
char	*ft_strbchr(char *str, char c)
{
	int		i;
	int		loc;
	char	*new;

	if (!str)
		return (NULL);
	loc = 0;
	while (str[loc])
	{
		if (str[loc] == c)
			break ;
		loc++;
	}
	new = malloc((loc + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i <= loc)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// Atoi but returns long long
long long	ft_atoi_long(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) > 0)
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

// Returns TRUE if str represent a valid long long number
int	ft_is_valid_num(char *str)
{
	int			i;
	long long	nb;
	char		*trim_str;

	trim_str = ft_strtrim(str, " ");
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (free(trim_str), FALSE);
		i++;
	}
	i = 0;
	if (trim_str[i] == '-' || trim_str[i] == '+')
		i++;
	nb = ft_atoi_long(trim_str);
	if (ft_strlen(&trim_str[i]) >= 19 && trim_str[0] == '-' && nb > 0)
		return (free(trim_str), FALSE);
	else if (ft_strlen(&trim_str[i]) > 19 && nb < 1000000000000000000)
		return (free(trim_str), FALSE);
	return (free(trim_str), TRUE);
}

// Free str and returns a copy of it, minus the character at index
char	*remove_index(char *str, int index, char c)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	if (str[index] != c)
		return (str);
	new = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < (int)ft_strlen(str))
	{
		if (j == index)
			i++;
		new[j++] = str[i++];
	}
	new[j] = '\0';
	free(str);
	if (ft_strncmp(new, "", 1) == 0)
		return (free(new), NULL);
	return (new);
}
