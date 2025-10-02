/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:02:14 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/18 10:24:34 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
	std::cout << "🤖 ClapTrap Default" << std::endl;
	name = "CL4P-TP";
	hit_points = 10;
	energy_points = 10;
	attack_damage = 0;
}

ClapTrap::ClapTrap(std::string	arg) {
	std::cout << "🤖 ClapTrap Name" << std::endl;
	name = arg;
	hit_points = 10;
	energy_points = 10;
	attack_damage = 0;
}

ClapTrap::ClapTrap(const ClapTrap& claptrap) {
	std::cout << "🤖 ClapTrap Copy" << std::endl;
	*this = claptrap;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& claptrap) {
	std::cout << "🤖 ClapTrap assignment operator" << std::endl;
	this->name = claptrap.name;
	this->hit_points = claptrap.hit_points;
	this->energy_points = claptrap.energy_points;
	this->attack_damage = claptrap.attack_damage;
	return (*this);
}

ClapTrap::~ClapTrap() {
	std::cout << "💀 ClapTrap " << this->getName() << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (this->energy_points > 0 && this->hit_points > 0)
	{
		std::cout << "🥊 " << this->name << " attacks " << target << " causing " 
		<< this->attack_damage << " point of damage !" << std::endl;
		this->energy_points--;
	}
	else if (this->energy_points == 0)
		std::cout << "🚫 " << this->name << " cannot attack (no energy point left)" << std::endl;
	else if (this->hit_points == 0)
		std::cout << "🚫 " << this->name << " cannot attack (no hit points left)" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	std::cout << "🤕 " << this->name << " takes " << amount << " damages !" << std::endl;
	if (this->hit_points >= amount)
		this->hit_points -= amount;
	else
		this->hit_points = 0;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (this->energy_points > 0 && hit_points > 0)
	{
		std::cout << "🔋 " << this->name << " repair itself, and gain " << amount 
			<< " hit_points back." << std::endl;
		this->energy_points--;
		this->hit_points += amount;
	}
	else if (this->energy_points == 0)
		std::cout << "🚫 " << this->name << " cannot repair itself (no energy point left)" << std::endl;
	else if (this->hit_points == 0)
		std::cout << "🚫 " << this->name << " cannot repair itself (no hit points left)" << std::endl;
}

std::string		ClapTrap::getName() const {
	return (this->name);
}