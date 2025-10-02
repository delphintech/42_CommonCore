/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:15:30 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:43:21 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure& arg) : AMateria(arg) {}

Cure& Cure::operator=(const Cure& arg) {
	AMateria::operator=(arg);
	return (*this);
}

Cure::~Cure() {}
	
Cure*	Cure::clone() const { 
	Cure	*clone;

	clone = new Cure();
	return (clone);
}

void	Cure::use(ICharacter& target) {
	std::cout << " heals " << target.getName() << "’s wounds *" << std::endl;
}