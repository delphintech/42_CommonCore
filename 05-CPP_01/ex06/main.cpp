/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:07:14 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/28 13:27:48 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Harl.hpp"

int	main(int ac, char **av)
{
	Harl		harl;
	std::string level[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	int			i;

	if (ac != 2)
	{
		std::cerr << "Bad input" << std::endl;
		return (1);
	}
	i = 0;
	while (i <= 4)
	{
		if (i < 4 && av[1] == level[i])
			break;
		i++;
	}
	switch (i)
	{
		case 0:
			std::cout << "[ DEBUG ]" << std::endl;
			harl.complain("DEBUG");
		case 1:
			std::cout << "[ INFO ]" << std::endl;
			harl.complain("INFO");
		case 2:
			std::cout << "[ WARNING ]" << std::endl;
			harl.complain("WARNING");
		case 3:
			std::cout << "[ ERROR ]" << std::endl;
			harl.complain("ERROR");
			break;
		default:
			std::cerr << "Bad input" << std::endl;
			return (1);
	}
	return (0);
}