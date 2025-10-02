/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:37:04 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 16:40:12 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string _type) {
	type = _type;
}

Weapon::~Weapon() {}

void	Weapon::setType(std::string params) { 
	this->type = params;
}

const std::string&	Weapon::getType(void) {
	return (this->type);
}