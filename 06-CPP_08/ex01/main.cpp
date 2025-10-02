/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:41:50 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/22 16:31:08 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include "Span.hpp"

void	print_test(std::string str) {
	std::cout << COLOR(36) << "/********** Test: '" << str << "' **********/" << COLOR(0) << std::endl;
}

int	main() {
	srand(time(0));
	print_test("Empty list");
	Span	empty;
	try {
		empty.addNumber(2);
	}
	catch (std::exception &e) {
		std::cout << COLOR(90) << "⚠️  " << e.what() << std::endl;
	}

	try {
		empty.shortestSpan();
		empty.shortestSpan();
	}
	catch (std::exception &e) {
		std::cout << COLOR(90) << "⚠️  " << e.what() << std::endl;
	}

	print_test("list of ten");
	Span	one(10);
	for (int i = 0; i < 10; i++) {
		one.addNumber(i);
	}
	std::cout << "Shortest: " << one.shortestSpan() << std::endl;
	std::cout << "Longest: " << one.longestSpan() << std::endl;

	print_test("Filling list too small");
	Span	two(50);
	try {
		two.fillRandom(100);
	}
	catch (std::exception &e) {
		std::cout << COLOR(90) << "⚠️  " << e.what() << std::endl;
	}

	print_test("List of 50 000 random numbers");
	Span	three(50000);
	three.fillRandom(50000);
	std::cout << "Shortest: " << three.shortestSpan() << std::endl;
	std::cout << "Longest: " << three.longestSpan() << std::endl;
}
