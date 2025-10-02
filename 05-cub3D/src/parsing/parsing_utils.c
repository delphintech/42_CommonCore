/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:49:26 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/19 15:20:48 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*fill_parsing(char **words, char *params)
{
	if (params)
	{
		free(params);
		return (NULL);
	}
	return (ft_strdup(words[1]));
}

int	is_allspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] != ' ')
			return (FALSE);
	return (TRUE);
}

int	ft_access(char *path, int oflag)
{
	int	fd;

	if (!path)
		return (FALSE);
	fd = open(path, oflag);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

char	*gnl_no_eol(int fd)
{
	char	*line;
	char	*new_str;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	new_str = ft_strtrim(line, "\n");
	free(line);
	return (new_str);
}

void	clear_cub(t_cub *cub)
{
	free(cub->north);
	free(cub->south);
	free(cub->east);
	free(cub->west);
	clear_tab(cub->map);
	free(cub);
}
