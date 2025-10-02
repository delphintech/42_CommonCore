/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:10:44 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/22 13:49:36 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <list>
#include <vector>

void	print_test(std::string str) {
	std::cout << COLOR(36) << "/********** Test: '" << str << "' **********/" << COLOR(0) << std::endl;
}

int	main() {
	int	arr[10] = { 5643, 43, -3, 0, 534, 88, 4352, 12, 88, -876543 };

	print_test("list");
	std::list<int>	list;
	for (int i = 0; i < 10; i++) {
		list.insert(list.begin(), arr[i]);
	}
	try {
		std::cout << *::easyfind(list, 88) << std::endl;
		std::cout << *::easyfind(list, 55) << std::endl;
	}
	catch (int n) {
		std::cout << COLOR(90) << "⚠️  " << n << " not found" << std::endl;
	}

	print_test("vector");
	std::vector<int>	vector;
	for (int i = 0; i < 10; i++) {
		vector.push_back(arr[i]);
	}
	try {
		std::cout << *::easyfind(vector, -3) << std::endl;
		std::cout << *::easyfind(vector, 118) << std::endl;
	}
	catch (int n) {
		std::cout << COLOR(90) << "⚠️  " << n << " not found" << std::endl;
	}
}
