/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:29:46 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 14:22:34 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name );

void	blue_print(std::string str)
{
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

int	main(void)
{
	int		i;
	Zombie	*horde;
	
	blue_print("Creating a horde of 10 zombies named Stevie Wanderer ...");
	horde = zombieHorde(10, "Stevie Wanderer");
	blue_print("Calling the horde ...");
	i = 0;
	while (i < 10)
		horde[i++].announce();
	blue_print("killing the horde ...");
	delete [] horde;
}