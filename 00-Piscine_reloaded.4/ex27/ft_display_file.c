/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:29:46 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/15 10:57:48 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int	ft_display(int fd)
{
	int		nb_read;
	char	buf[128];

	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buf, 128);
		if (nb_read == -1)
		{
			write(1, "Cannot read file.\n", 18);
			return (-1);
		}
		buf[nb_read] = '\0';
		write(1, buf, nb_read);
	}
	close(fd);
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;
	int	rd;

	if (ac < 2)
	{
		write(1, "File name missing.\n", 19);
		return (0);
	}
	if (ac > 2)
	{
		write(1, "Too many arguments.\n", 20);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Cannot read file.\n", 18);
		return (0);
	}
	rd = ft_display(fd);
	if (rd == -1)
		return (0);
}
