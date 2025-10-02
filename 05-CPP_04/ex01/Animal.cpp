/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:59:38 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:04:35 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() {
	std::cout << COLOR(90) << "🐾 Default" << COLOR(0) << std::endl;
	type = "Unknown";
}

Animal::Animal(std::string arg) {
	std::cout << COLOR(90) << "🐾 Type" << COLOR(0) << std::endl;
	type = arg;
}

Animal::Animal(const Animal& arg) {
	std::cout << COLOR(90) << "🐾 Copy" << COLOR(0) << std::endl;
	*this = arg;
}

Animal&	Animal::operator=(const Animal& arg) {
	std::cout << COLOR(90) << "🐾 Assignment operator" << COLOR(0) << std::endl;
	this->type = arg.type;
	return (*this);
}

Animal::~Animal() {
	std::cout << COLOR(90) << "💀  Animal" << COLOR(0) << std::endl;
}

std::string	Animal::getType() const {
	return (this->type);
}

void	Animal::makeSound() const {
	std::cout << COLOR(33) << "??? ... ??? ..." << COLOR(0) << std::endl;
}
