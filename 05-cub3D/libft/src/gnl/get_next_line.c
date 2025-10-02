/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:29:26 by dabouab           #+#    #+#             */
/*   Updated: 2024/10/29 16:54:44 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/libft.h"

static int	find_end_line(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (ft_strlen(str));
}

static int	has_eol(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*use_rest(char *str, char *rest)
{
	int	i;

	if (rest[0] != '\0')
	{
		i = find_end_line(&rest[0]);
		str = ft_strljoin_gnl(str, &rest[0], i + 2);
		ft_strlcpy_gnl(&rest[0], &rest[i + 1], ft_strlen(&rest[0]) - i);
	}	
	return (str);
}

char	*get_next_line(int fd)
{
	int				i;
	int				nbread;
	static char		rest[BUFFER_SIZE + 1];
	char			*buf;
	char			*str;

	buf = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buf || (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0))
		return (free(buf), NULL);
	nbread = -1;
	str = NULL;
	str = use_rest(str, &rest[0]);
	while (nbread != 0 && rest[0] == '\0' && has_eol(str) == 0)
	{
		nbread = read(fd, buf, BUFFER_SIZE);
		buf[nbread] = '\0';
		i = find_end_line(buf);
		if ((size_t)i != ft_strlen(buf))
			nbread = 0;
		str = ft_strljoin_gnl(str, buf, i + 2);
		if (!str || str[0] == 0)
			return (free(buf), free(str), NULL);
		ft_strlcpy_gnl(&rest[0], &buf[i + 1], ft_strlen(buf) - i);
	}
	return (free(buf), str);
}
// TO DO: protect read (if it returns -1, clear buf and rest to restart to read)