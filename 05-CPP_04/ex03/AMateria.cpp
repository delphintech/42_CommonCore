/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:09:32 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/11 17:38:45 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria*	AMateria::drops[MAX_DROPS] = {NULL};

AMateria::AMateria() : _type("unknown") {}

AMateria::AMateria(const std::string& arg) : _type(arg) {}

AMateria::AMateria(const AMateria& arg) {
	*this = arg;
}

AMateria& AMateria::operator=(const AMateria& arg) {
	this->_type = arg._type;
	return (*this);
}

AMateria::~AMateria() {}
	
const std::string&	AMateria::getType() const {
	return (this->_type);
}

void	AMateria::add_drop(AMateria *materia) {
	for (int i = 0; i < MAX_DROPS; i++)
	{
		if (!AMateria::drops[i])
		{
			AMateria::drops[i] = materia;
			break ;
		}
	}
}

void	AMateria::take_drop(AMateria *materia) {
	int	i;

	i = 0;
	while (i < MAX_DROPS)
	{
		if (AMateria::drops[i] == materia)
		{
			AMateria::drops[i] = NULL;
			break ;
		}
		i++;
	}
}
