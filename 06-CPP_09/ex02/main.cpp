/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:04:01 by dabouab           #+#    #+#             */
/*   Updated: 2025/03/20 13:14:23 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iomanip>

int	error() {
	std::cout << "Error" << std::endl;
	return (1);
}

int	main(int ac, char** av) {
	clock_t		t;

	/********** VECTOR **********/
	PmergeMe<std::vector>	vector(ac, av);

	if (vector.getSize() == 0)
		return (error());

	// Before
	std::cout << std::setw(10) << std::left << "Before: ";
	vector.display();

	// Algo
	t = std::clock();
	vector.fordJohnson();
	t = std::clock() - t;

	// After
	std::cout << std::setw(10) << std::left << "After: ";
	vector.display();

	// Time
	std::cout << "Time to process a range of " << vector.getSize();
	std::cout << " elements with std::vector : " << ((float)t * 1000) / CLOCKS_PER_SEC << " msec" << std::endl;

	/********** LIST **********/
	PmergeMe<std::list>		list(ac, av);

	// Algo
	t = std::clock();
	list.fordJohnson();
	t = std::clock() - t;

	// Time
	std::cout << "Time to process a range of " << list.getSize();
	std::cout << " elements with std::list : " << ((float)t * 1000) / CLOCKS_PER_SEC << " msec" << std::endl;
}
