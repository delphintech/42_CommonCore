/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:59 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/03 14:12:06 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>

// ---------- Exercice 00 ---------- //
const int	Fixed::_fract = 8;

Fixed::Fixed() {
	std::cout << "Default Constructor called" << std::endl;
	_raw = 0;
}

Fixed::Fixed(const Fixed& fixed) {
	std::cout << "Copy constructor called" << std::endl;
	*this = fixed;
}

Fixed& Fixed::operator=(const Fixed& fixed) {
	std::cout << "Copy assignment operator called" << std::endl;
	this->_raw = fixed.getRawBits();
	return (*this);
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}
	
int		Fixed::getRawBits(void) const {
	return (this->_raw);
}

void	Fixed::setRawBits(int const raw) {
	this->_raw = raw;	
}

// ---------- Exercice 01 ---------- //
Fixed::Fixed(int params) {
	std::cout << "Int Constructor called" << std::endl;
	_raw = params << _fract;
}

Fixed::Fixed(float params) {
	std::cout << "Float Constructor called" << std::endl;
	_raw = roundf(params * (1 << _fract));
}

float	Fixed::toFloat(void) const {
	return ((float)this->_raw / (1 << this->_fract));
}

int		Fixed::toInt(void) const {
	return (this->_raw >> this->_fract);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}