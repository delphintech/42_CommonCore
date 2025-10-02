/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:26:51 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:04:35 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {
	std::cout << COLOR(90) << "👾 Default" << COLOR(0) << std::endl;
	type = "Unknown";
}

WrongAnimal::WrongAnimal(std::string arg) {
	std::cout << COLOR(90) << "👾 Type" << COLOR(0) << std::endl;
	type = arg;
}

WrongAnimal::WrongAnimal(const WrongAnimal& arg) {
	std::cout << COLOR(90) << "👾 Copy" << COLOR(0) << std::endl;
	*this = arg;
}

WrongAnimal&	WrongAnimal::operator=(const WrongAnimal& arg) {
	std::cout << COLOR(90) << "👾 Assignment operator" << COLOR(0) << std::endl;
	this->type = arg.type;
	return (*this);
}

WrongAnimal::~WrongAnimal() {
	std::cout << COLOR(90) << "💀 Wrong Animal" << COLOR(0) << std::endl;
}

std::string	WrongAnimal::getType() const {
	return (this->type);
}

void	WrongAnimal::makeSound() const {
	std::cout << COLOR(33) << "💤 ... 💤 ..." << COLOR(0) << std::endl;
}
