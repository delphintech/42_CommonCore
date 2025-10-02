/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:22:46 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/04 17:26:02 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "👽 FragTrap Default" << std::endl;
	this->hit_points = 100;
	this->energy_points = 100;
	this->attack_damage = 30;
}

FragTrap::FragTrap(std::string arg) : ClapTrap(arg) {
	std::cout << "👽 FragTrap Name" << std::endl;
	this->hit_points = 100;
	this->energy_points = 100;
	this->attack_damage = 30;
}

FragTrap::FragTrap(const FragTrap& fragtrap) : ClapTrap(fragtrap) {
	std::cout << "👽 FragTrap Copy" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& fragtrap) {
	std::cout << "👽 FragTrap assignment operator" << std::endl;
	this->ClapTrap::operator=(fragtrap);
	return (*this);
}

FragTrap::~FragTrap() {
	std::cout << "💀 FragTrap: " << this->getName() << std::endl;
}

void	FragTrap::highFivesGuys(void) {
	if (this->energy_points > 0 && this->hit_points > 0)
		std::cout << this->getName() << ": ✋" << std::endl;	else if (this->energy_points == 0)
		std::cout << "🚫 " << this->getName() << " has no juice" << std::endl;
	else if (this->hit_points == 0)
		std::cout << "🚫 " << this->getName() << " has no hit points left" << std::endl;
}
