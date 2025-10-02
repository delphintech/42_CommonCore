/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:48:52 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 16:37:49 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string _name) {
	name = _name;
	weapon = NULL;
}

HumanB::~HumanB() {}

void	HumanB::attack(void) {
	std::cout << this->name << " attacks with ";
	if (this->weapon)
		std::cout <<  "their " << this->weapon->getType() << std::endl;
	else
		std::cout <<  "... Nothing 😱" << std::endl;
}

void	HumanB::setWeapon(Weapon &_weapon) {
	this->weapon = &_weapon;
}