/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:58:41 by dabouab           #+#    #+#             */
/*   Updated: 2024/08/02 15:25:15 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	find_end_line(char *str)
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

char	*use_rest(char *str, char *rest)
{
	int	i;

	if (rest[0] != '\0')
	{
		i = find_end_line(rest);
		str = ft_strljoin_gnl(str, &rest[0], i + 2);
		ft_strlcpy_gnl(rest, &rest[i + 1], ft_strlen(rest) - i);
	}
	return (str);
}

char	*ft_return(char *str, char *buf)
{
	free(buf);
	if (str[0] == 0)
		return (free(str), NULL);
	return (str);
}

char	*set_rest(int fd)
{
	static t_rest	*list;
	t_rest			*temp;

	temp = list;
	while (temp && temp->fd != fd)
		temp = temp->next;
	if (!temp)
	{
		temp = ft_lstnew_gnl(fd);
		ft_lstadd_back_gnl(&list, temp);
	}
	return (&(temp->rest[0]));
}

char	*get_next_line(int fd)
{
	size_t			i;
	int				nbread;
	char			*rest;
	char			*buf;
	char			*str;

	buf = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buf || (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0))
		return (free(buf), NULL);
	rest = set_rest(fd);
	nbread = -1;
	str = NULL;
	str = use_rest(str, rest);
	while (nbread != 0 && rest[0] == '\0')
	{
		nbread = read(fd, buf, BUFFER_SIZE);
		buf[nbread] = '\0';
		i = find_end_line(buf);
		if (i != ft_strlen(buf))
			nbread = 0;
		str = ft_strljoin_gnl(str, buf, i + 2);
		ft_strlcpy_gnl(rest, &buf[i + 1], ft_strlen(buf) - i);
	}
	return (ft_return(str, buf));
}

// TO DO: protect read (if it returns -1, clear buf and rest to restart to read)
// TO DO: erase the node list when the enf of the file is reach
// TO DO: check for leaks
