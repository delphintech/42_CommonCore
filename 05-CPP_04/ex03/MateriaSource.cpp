/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:53:16 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/11 15:45:26 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4 ; i++)
		_inventory[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &arg) {
	for (int i = 0; i < 4; i++)
		if (arg._inventory[i])
			this->_inventory[i] = arg._inventory[i]->clone();
}

MateriaSource& MateriaSource::operator=(const MateriaSource &arg) {
	for (int i = 0; i < 4; i++)
		delete this->_inventory[i];

	for (int i = 0; i < 4; i++)
		if (arg._inventory[i])
			this->_inventory[i] = arg._inventory[i]->clone();
	return (*this);
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < 4; i++)
		delete this->_inventory[i];
}

void MateriaSource::learnMateria(AMateria *materia) {
	for (int i = 0; i < 4; i++)
		if (!this->_inventory[i])
		{
			this->_inventory[i] = materia->clone();
			break ;
		}
}

AMateria* MateriaSource::createMateria(std::string const & type) {
	AMateria	*copy;

	copy = 0;
	for (int i = 0; i < 4; i++)
	{
		if (this->_inventory[i]->getType() == type)
		{
			copy = this->_inventory[i]->clone();
			break ;
		}
	}
	return (copy);
}
