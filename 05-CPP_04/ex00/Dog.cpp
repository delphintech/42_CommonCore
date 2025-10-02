/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:47:56 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:01:50 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
	std::cout << COLOR(90) << "🐕 Default" << COLOR(0) << std::endl;
}

Dog::Dog(const Dog& arg) : Animal(arg) {
	std::cout << COLOR(90) << "🐕 Copy" << COLOR(0) << std::endl;
}

Dog&	Dog::operator=(const Dog& arg) {
	std::cout << COLOR(90) << "🐕 Assignment operator" << COLOR(0) << std::endl;
	Animal::operator=(arg);
	return (*this);
}

Dog::~Dog() {
	std::cout << COLOR(90) << "💀  Dog" << COLOR(0) << std::endl;
}

void	Dog::makeSound() const {
	std::cout << COLOR(33) << "Woof ... Woof ..." << COLOR(0) << std::endl;
}
