/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:31:40 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/16 10:40:47 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

void	blue_print(std::string str) {
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

int main( void )
{
	Fixed		a;
	Fixed const	b(Fixed(5.05f ) * Fixed(2));
	Fixed		c;
	
	c = b + 5.2f;
	blue_print("Operateur de comapraison:");
	std::cout << std::boolalpha;
	std::cout << (a < b) << std::endl;
	std::cout << (a > b) << std::endl;
	std::cout << (a <= b) << std::endl;
	std::cout << (a >= b) << std::endl;
	std::cout << (a == b) << std::endl;
	std::cout << (a != b) << std::endl;
	
	blue_print("Operateurs d'incrementation:");
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << c << std::endl;
	std::cout << c-- << std::endl;
	std::cout << c << std::endl;
	std::cout << --c << std::endl;
	std::cout << c << std::endl;
	
	blue_print("Operateurs arithmetiques:");
	std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
	std::cout << a + c << std::endl;
	std::cout << c - a << std::endl;
	std::cout << a * b << std::endl;
	std::cout << c / b << std::endl;
	
	blue_print("Fonctions membres statiques:");
	std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	std::cout << Fixed::min( b, c ) << std::endl;
	return 0;
}
