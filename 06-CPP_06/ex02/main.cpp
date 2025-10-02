/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:44 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 16:04:06 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

void	print_test(std::string str) {
	std::cout << COLOR(36) << "/********** Test: \'" << str
		<< "\' **********/" << COLOR(0) << std::endl;
}

int main() {
	Base	*ptr;

	srand(time(0));

	print_test("1");
	ptr = Base::generate();
	Base::identify(ptr);
	Base::identify(*ptr);
	delete ptr;
	std::cout << std::endl;

	print_test("2");
	ptr = Base::generate();
	Base::identify(ptr);
	Base::identify(*ptr);
	delete ptr;
	std::cout << std::endl;

	print_test("3");
	ptr = Base::generate();
	Base::identify(ptr);
	Base::identify(*ptr);
	delete ptr;
	std::cout << std::endl;

	return (0);
}
