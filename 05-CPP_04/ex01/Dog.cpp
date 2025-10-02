/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:47:56 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:02:02 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
	std::cout << COLOR(90) << "🐕 Default" << COLOR(0) << std::endl;
	brain = new Brain();
}

Dog::Dog(const Dog& arg) : Animal(arg) {
	std::cout << COLOR(90) << "🐕 Copy" << COLOR(0) << std::endl;
	this->brain = new Brain;
	*this->brain = *arg.brain;
}

Dog&	Dog::operator=(const Dog& arg) {
	std::cout << COLOR(90) << "🐕 Assignment operator" << COLOR(0) << std::endl;
	Animal::operator=(arg);
	*this->brain = *arg.brain;
	return (*this);
}

Dog::~Dog() {
	std::cout << COLOR(90) << "💀  Dog" << COLOR(0) << std::endl;
	delete brain;
}

void	Dog::makeSound() const {
	std::cout << COLOR(33) << "Woof ... Woof ..." << COLOR(0) << std::endl;
}

Brain	*Dog::getBrain() const {
	return (this->brain);
}