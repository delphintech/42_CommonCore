/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:24:18 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:03:53 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

void	blue_print(std::string str) {
	std::cout << COLOR(34;1) << str << COLOR(0) << std::endl;
}

int	main()
{
	Animal	animal;
	Dog		dog;
	Cat		cat;

	blue_print(dog.getType() + " :");
	dog.makeSound();
	blue_print(cat.getType() + " :");
	cat.makeSound();
	blue_print(animal.getType() + " :");
	animal.makeSound();

	WrongAnimal	wgan;
	WrongCat	wgcat;
	blue_print(wgan.getType() + " :");
	wgan.makeSound();
	blue_print(wgcat.getType() + " :");
	wgcat.makeSound();
}
