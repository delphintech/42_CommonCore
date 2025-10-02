/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:24:18 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:19:15 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"

void	blue_print(std::string str) {
	std::cout << COLOR(34;1) << str << COLOR(0) << std::endl;
}

int	main()
{
	// Animal	test;
	Dog		dog;
	Cat		cat;

	blue_print(dog.getType() + " :");
	dog.makeSound();
	blue_print(cat.getType() + " :");
	cat.makeSound();
}
