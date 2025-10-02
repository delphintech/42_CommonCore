/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:28:18 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:08:24 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
	std::cout << COLOR(90) << "🐯 Default" << COLOR(0) << std::endl;
}

WrongCat::WrongCat(const WrongCat& arg) : WrongAnimal(arg) {
	std::cout << COLOR(90) << "🐯 Copy" << COLOR(0) << std::endl;
}

WrongCat&	WrongCat::operator=(const WrongCat& arg) {
	std::cout << COLOR(90) << "🐯 Assignment operator" << COLOR(0) << std::endl;
	WrongAnimal::operator=(arg);
	return (*this);
}

WrongCat::~WrongCat() {
	std::cout << COLOR(90) << "💀  WrongCat" << COLOR(0) << std::endl;
}
