/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:31:31 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:01:44 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
	std::cout << COLOR(90) << "🐈 Default" << COLOR(0) << std::endl;
}

Cat::Cat(const Cat& arg) : Animal(arg) {
	std::cout << COLOR(90) << "🐈 Copy" << COLOR(0) << std::endl;
}

Cat&	Cat::operator=(const Cat& arg) {
	std::cout << COLOR(90) << "🐈 Assignment operator" << COLOR(0) << std::endl;
	Animal::operator=(arg);
	return (*this);
}

Cat::~Cat() {
	std::cout << COLOR(90) << "💀  Cat" << COLOR(0) << std::endl;
}

void	Cat::makeSound() const {
	std::cout << COLOR(33) << "Miaou ... Miaou ..." << COLOR(0) << std::endl;
}
