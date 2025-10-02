/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:29:46 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 13:18:42 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void	randomChump(std::string name);

void	blue_print(std::string str)
{
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

int	main(void)
{
	Zombie	*chump;

	blue_print("Creating a Zombie with newZombie ...");
	chump = newZombie("Crawly Billy");
	blue_print("Creating a Zombie with randomChump ...");
	randomChump("Brainy Dumbdumb");
	blue_print("Using the newZombie one...");
	chump->announce();
	delete chump;
}