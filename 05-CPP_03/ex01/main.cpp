/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:42:40 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/18 10:19:23 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

void	blue_print(std::string str) {
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

int	main()
{
	ClapTrap	one;
	ScavTrap	two;
	ScavTrap	three = ScavTrap("Rusty");
	
	one.attack(two.getName());
	two.attack(one.getName());
	one.takeDamage(20);
	one.beRepaired(10);
	two.attack(three.getName());
	three.takeDamage(20);
	three.beRepaired(10);
	two.attack(three.getName());
	three.takeDamage(20);
	two.attack(three.getName());
	three.takeDamage(20);
	three.attack(two.getName());
	two.guardGate();
}