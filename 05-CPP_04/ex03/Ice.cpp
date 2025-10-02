/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:57:23 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/11 17:47:59 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice& arg) : AMateria(arg) {}

Ice& Ice::operator=(const Ice& arg) {
	AMateria::operator=(arg);
	return (*this);
}

Ice::~Ice() {}
	
Ice*	Ice::clone() const { 
	Ice	*clone;

	clone = new Ice();
	return (clone);
}

void				Ice::use(ICharacter& target) {
	std::cout << " shoots an ice bolt at " << target.getName() << " *" << std::endl;
}