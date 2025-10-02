/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:34 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/23 14:46:24 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <list>

void	print_test(std::string str) {
	std::cout << COLOR(36) << "/********** Test: '" << str << "' **********/" << COLOR(0) << std::endl;
}

int 	main() {
	print_test("MutantStack");
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	MutantStack<int>::reverse_iterator rit = mstack.rbegin();
	MutantStack<int>::reverse_iterator rite = mstack.rend();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << "Reverse" << std::endl;
	while (rit != rite)
	{
		std::cout << *rit << std::endl;
		++rit;
	}
	std::stack<int> s(mstack);

	print_test("List");
	std::list<int> list;
	list.push_back(5);
	list.push_back(17);
	std::cout << list.back() << std::endl;
	list.pop_back();
	std::cout << list.size() << std::endl;
	list.push_back(3);
	list.push_back(5);
	list.push_back(737);
	//[...]
	list.push_back(0);
	std::list<int>::iterator itl = list.begin();
	std::list<int>::iterator itle = list.end();
	std::list<int>::reverse_iterator ritl = list.rbegin();
	std::list<int>::reverse_iterator ritle = list.rend();
	++itl;
	--itl;
	while (itl != itle)
	{
		std::cout << *itl << std::endl;
		++itl;
	}
	std::cout << "Reverse" << std::endl;
	while (ritl != ritle)
	{
		std::cout << *ritl << std::endl;
		++ritl;
	}
	return 0;
}
