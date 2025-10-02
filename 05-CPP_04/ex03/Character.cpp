/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:59:13 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 11:20:53 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"

Character::Character() : _name("unknown"), _inventory() {}

Character::Character(std::string arg) : _name(arg), _inventory() {}

Character::Character(const Character& arg) : _inventory(){
	this->_name = arg._name;
	for (int i = 0; i < 4; i++)
		if (arg._inventory[i])
			this->_inventory[i] = arg._inventory[i]->clone();
}

Character& Character::operator=(const Character& arg) {	
	this->_name = arg._name;
	for (int i = 0; i < 4; i++)
		delete this->_inventory[i];
	for (int i = 0; i < 4; i++)
		if (arg._inventory[i])
			this->_inventory[i] = arg._inventory[i]->clone();
	return (*this);
}

Character::~Character() {
	for (int i = 0; i < 4; i++)
		if (this->_inventory[i])
			delete this->_inventory[i];
};

const std::string& Character::getName() const {
	return (this->_name);
}

void Character::equip(AMateria* m) {
	int	i;
	
	i = 0;
	while (this->_inventory[i])
		i++;
	if (i < 4)
	{
		this->_inventory[i] = m;
		AMateria::take_drop(m);
	}
}

void Character::unequip(int idx) {
	if (idx < 0 || idx > 3)
		return ;
	if (!this->_inventory[idx])
		return ;
	AMateria::add_drop(this->_inventory[idx]);
	this->_inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx > 3)
		return ;
	if (!this->_inventory[idx])
		return ;
	std::cout << "* " << this->_name;
	this->_inventory[idx]->use(target);
}
