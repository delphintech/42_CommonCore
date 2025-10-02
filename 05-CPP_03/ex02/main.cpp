/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:42:40 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/18 10:29:01 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

void	blue_print(std::string str) {
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

int	main()
{
	ClapTrap	clap = ClapTrap("clap");
	ScavTrap	scav = ScavTrap("scav");
	FragTrap	frag = FragTrap("frag");
	FragTrap	copy = frag;
	
	std::cout << "Copy name : " << copy.getName() << std::endl;
	clap.attack("frag");
	scav.attack("clap");
	clap.takeDamage(20);
	clap.attack("frag");
	frag.highFivesGuys();
	frag.beRepaired(10);
	frag.attack("scrav");
	scav.takeDamage(30);
	frag.attack("scrav");
	scav.takeDamage(30);
	frag.attack("scrav");
	scav.takeDamage(30);
	frag.attack("scrav");
	scav.takeDamage(30);
	scav.attack("frag");
}