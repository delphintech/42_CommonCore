/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:58 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/11 10:49:17 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <stdlib.h>

int	ft_error(std::string str)
{
	std::cerr << str << std::endl;
	exit (EXIT_FAILURE);
}

void	replace(std::string file_name, std::string s1, std::string s2)
{
	int				i;
	std::fstream	file;
	std::ofstream	new_file;
	std::string		line;

	file.open(file_name.c_str(), std::fstream::in);
	if (!file.is_open())
		ft_error("No such file or directory");
	new_file.open((file_name + ".replace").c_str(), std::fstream::out);
	if (!new_file.is_open())
		ft_error("New file creation failed");
	while (std::getline(file, line))
	{
		if (s1.empty())
			i = -1;
		else
			i = line.find(s1);
		while (i != -1)
		{
			line = line.erase(i, s1.length());
			line = line.insert(i, s2);
			i = line.find(s1);
		}
		new_file << line.c_str() << std::endl;
	}
	file.close();
	new_file.close();
}

int	main(int ac, char **av)
{
	if (ac != 4)
		ft_error("Bad input");
	
	replace(av[1], av[2], av[3]);
}
