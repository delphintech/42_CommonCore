/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:27:44 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/18 10:22:57 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() {
	std::cout << "👾 ScavTrap Default" << std::endl;
	this->name = "SC4V-TP";
	this->hit_points = 100;
	this->energy_points = 50;
	this->attack_damage = 20;
}

ScavTrap::ScavTrap(std::string arg) : ClapTrap(arg) {
	std::cout << "👾 ScavTrap Name" << std::endl;
	this->hit_points = 100;
	this->energy_points = 50;
	this->attack_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap& scavtrap) : ClapTrap(scavtrap) {
	std::cout << "👾 ScavTrap Copy" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& scavtrap) {
	std::cout << "👾 ScavTrap assignment operator" << std::endl;
	this->ClapTrap::operator=(scavtrap);
	return (*this);
}

ScavTrap::~ScavTrap() {
	std::cout << "💀 Scavtrap " << this->getName() << std::endl;
}

void ScavTrap::attack(const std::string& target) { 
	if (this->energy_points > 0 && this->hit_points > 0)
	{
		std::cout << "🔨 " << this->name << " smash " << target << " and cause " 
		<< this->attack_damage << " damages !" << std::endl;
		this->energy_points--;
	}
	else if (this->energy_points == 0)
		std::cout << "🚫 " << this->name << " has no juice" << std::endl;
	else if (this->hit_points == 0)
		std::cout << "🚫 " << this->name << " has no hit points left" << std::endl;
}

void ScavTrap::guardGate() {
	if (this->energy_points > 0 && this->hit_points > 0)
		std::cout << "🚪 " << this->name << " is now in Gate keeper mode " << std::endl;
	else if (this->energy_points == 0)
		std::cout << "🚫 " << this->name << " has no juice" << std::endl;
	else if (this->hit_points == 0)
		std::cout << "🚫 " << this->name << " has no hit points left" << std::endl;
}