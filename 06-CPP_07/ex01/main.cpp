/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:09:06 by dabouab           #+#    #+#             */
/*   Updated: 2025/03/19 15:29:41 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Iter.hpp"

void	print_test(std::string str) {
	std::cout << COLOR(36) << "/********** Test: '" << str << "' **********/" << COLOR(0) << std::endl;
}

int	main() {
	print_test("int array");
	int arr[5] = {1, 2, 3, 4, 5};
	iter(arr, 5, &display);
	std::cout << std::endl;

	print_test("string array");
	std::string list[6] = {"one", "two", "three", "four", "five", "six"};
	iter(list, 6, &display);
}
