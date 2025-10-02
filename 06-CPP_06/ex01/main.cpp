/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:47:40 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/20 17:36:44 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

void	print_test(std::string str) {
	std::cout << COLOR(36) << "/********** Test: \'" << str
		<< "\' **********/" << COLOR(0) << std::endl;
}

int	main() {
	uintptr_t	ptr;
	Data		test;
	
	/********** Test 1 **********/
	print_test("str = eight & i = 8");
	Data	d(8, "eight");
	d.display();
	
	ptr = Serializer::serialize(&d);
	
	test = *Serializer::deserialize(ptr);
	test.display();

	/********** Test 2 **********/
	print_test("str = "" & i = 0");
	Data	zero(0, "");
	zero.display();
	
	ptr = Serializer::serialize(&zero);
	
	test = *Serializer::deserialize(ptr);
	test.display();
	
	return (0);
}