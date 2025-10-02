/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:42:40 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/04 18:00:35 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

void	blue_print(std::string str) {
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

int	main()
{
	ClapTrap		clap = ClapTrap("clap");
	DiamondTrap		diam = DiamondTrap("diam");
	DiamondTrap		copy;
	
	copy.whoAmI();
	copy = diam;
	copy.whoAmI();
	diam.attack(copy.getName());
	diam.highFivesGuys();
	diam.guardGate();
}