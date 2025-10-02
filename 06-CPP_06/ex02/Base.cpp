/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:39:28 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 16:04:26 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {}

Base*	Base::generate(void) {
	int	n;

	n = 1 + rand() % 3;
	switch (n)
	{
	case 1:
		return (new A());
	case 2:
		return (new B());
	case 3:
		return (new C());
	}
	return (new A());
}

void	Base::identify(Base* p) {
	std::cout << "Object type by pointer: ";

	A *a = dynamic_cast<A*>(p);
	B *b = dynamic_cast<B*>(p);
	C *c = dynamic_cast<C*>(p);

	if (a)
		std::cout << "A" << std::endl;
	else if (b)
		std::cout << "B" << std::endl;
	else if (c)
		std::cout << "C" << std::endl;
}

void	Base::identify(Base& p) {
	std::cout << "Object type by reference: ";

	A *a = dynamic_cast<A*>(&p);
	B *b = dynamic_cast<B*>(&p);
	C *c = dynamic_cast<C*>(&p);

	if (a)
		std::cout << "A" << std::endl;
	else if (b)
		std::cout << "B" << std::endl;
	else if (c)
		std::cout << "C" << std::endl;
}
