/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:43:31 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/18 10:32:25 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap() {
	std::cout << "💎 Diamond Default" << std::endl;
	name = "DI4M-TP";
	ClapTrap::name = name + "_clap_name";
}

DiamondTrap::DiamondTrap(std::string arg) : ClapTrap(arg) {
	std::cout << "💎 Diamond Name" << std::endl;
	name = arg;
	ClapTrap::name += "_clap_name";
	hit_points = FragTrap::hit_points;
	energy_points = ScavTrap::energy_points;
	attack_damage = FragTrap::attack_damage;
}

DiamondTrap::DiamondTrap(const DiamondTrap& trap) : ClapTrap(trap) {
	std::cout << "💎 Diamond Copy" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& trap) {
	std::cout << "💎 Diamond Assignment operator" << std::endl;
	this->name = trap.name;
	ClapTrap::operator=(trap);
	return (*this);
}

DiamondTrap::~DiamondTrap() {
	std::cout << "💀 DiamondTrap: " << this->getName() << std::endl;
}

void DiamondTrap::whoAmI() {
	std::cout << "My name is: " << this->name << ", but my Claptrap name is: " 
		<< this->ClapTrap::name << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}