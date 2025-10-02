/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:28:46 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 14:43:24 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>

void	blue_print(std::string str) {
	std::cout << "\e[34m" << std::left << std::setw(28) << str << "\e[0m";
	std::cout.flush();
}

int	main()
{
	std::string	str;
	std::string	*stringPTR;
	std::string	&stringREF = str;

	str = "HI THIS IS BRAIN";
	stringPTR = &str;
	blue_print("Memory adress of str: ");
	std::cout << &str << std::endl;
	blue_print("Memory adress of stringPTR: ");
	std::cout << stringPTR << std::endl;
	blue_print("Memory adress of stringREF: ");
	std::cout << &stringREF << std::endl;
	blue_print("Value of str: ");
	std::cout << str << std::endl;
	blue_print("Value of stringPTR: ");
	std::cout << *stringPTR << std::endl;
	blue_print("Value of stringREF: ");
	std::cout << stringREF << std::endl;
}

