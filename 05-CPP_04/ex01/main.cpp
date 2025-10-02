/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:24:18 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:39:38 by dabouab          ###   ########.fr       */
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
	int		i = 0;
	Animal	*animals[10];

	blue_print("Testing the array of animals: ");
	while (i < 10)
	{
		if (i < 5)
			animals[i] = new Cat();
		else
			animals[i] = new Dog();
		i++;
	}
	i = 0;
	while (i < 10)
		animals[i++]->makeSound();
	i = 0;
	while (i < 10)
		delete animals[i++];
	
	blue_print("Testing the deep copy: ");
	Cat	cat;
	cat.getBrain()->add_idea("🐁");
	cat.getBrain()->add_idea("🧀");
	
	Cat	copy = Cat(cat);
	Cat another;
	another = cat;
	
	std::cout << "Brain adress of cat: " << cat.getBrain() << std::endl;
	cat.getBrain()->show_ideas();
	std::cout << "Brain adress of copy: " << copy.getBrain()  << std::endl;
	copy.getBrain()->show_ideas();
	std::cout << "Brain adress of another: " << another.getBrain()  << std::endl;
	another.getBrain()->show_ideas();
}
