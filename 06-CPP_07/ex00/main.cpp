/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:52:26 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 17:24:47 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Template.hpp"
#include <iostream>

void	print_test(std::string str) {
	std::cout << COLOR(36) << "/********** Test: '" << str << "' **********/" << COLOR(0) << std::endl;
}

int main( void ) {
	int a = 2;
	int b = 3;

	print_test("1");
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;

	print_test("2");
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	return 0;
}
