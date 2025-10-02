/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:54:57 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/20 16:58:01 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

/********** Canonical **********/
Data::Data() : _str(""), _i(0) {};

Data::Data(int i, std::string str) : _str(str), _i(i) {};

Data::Data(const Data& obj)  : _str(obj._str), _i(obj._i) {};

Data& Data::operator=(const Data& obj) {
	this->_str = obj._str;
	this->_i = obj._i;
	return (*this);
}

Data::~Data() {}

/********** Getters **********/
std::string	Data::getStr() const { return (this->_str); }
int			Data::getI() const { return (this->_i); }

void		Data::display() const {
	std::cout << "Data: str=" << this->_str << " / i=" << this->_i << ";" << std::endl;
}