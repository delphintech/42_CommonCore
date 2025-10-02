/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:42:40 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/04 12:50:49 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

void	blue_print(std::string str) {
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

int	main()
{
	ClapTrap	one;
	ClapTrap	two = ClapTrap("Scrappy");

	one.attack("a wild bear");
	one.attack("the wild bear");
	blue_print("A wild bear attack one & two");
	one.takeDamage(5);
	two.takeDamage(5);
	one.beRepaired(6);
	blue_print("The wild bear strikes again");
	one.takeDamage(5);
	two.takeDamage(5);
	one.attack("a wild bear");
	two.attack("the wild bear");
	blue_print("The wild bear runs away");
}