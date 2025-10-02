/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:59 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:15:48 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

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

// ---------- Exercice 02 ---------- //
	// ----- Comparison ----- //
bool	Fixed::operator>(const Fixed &fixed) const {
	return (this->toFloat() > fixed.toFloat());
}

bool	Fixed::operator<(const Fixed &fixed) const {
	return (this->toFloat() < fixed.toFloat());
}

bool	Fixed::operator>=(const Fixed &fixed) const {
	return (this->toFloat() >= fixed.toFloat());
}

bool	Fixed::operator<=(const Fixed &fixed) const {
	return (this->toFloat() <= fixed.toFloat());
}

bool	Fixed::operator==(const Fixed &fixed) const {
	return (this->toFloat() == fixed.toFloat());
}

bool	Fixed::operator!=(const Fixed &fixed) const {
	return (this->toFloat() != fixed.toFloat());
}

	// ----- Operation ----- //
Fixed	Fixed::operator+(const Fixed &fixed) const {
	Fixed	result;

	result.setRawBits(this->_raw + fixed._raw);
	return (result);
}

Fixed	Fixed::operator-(const Fixed &fixed) const {
	Fixed	result;

	result.setRawBits(this->_raw - fixed._raw);
	return (result);
}

Fixed	Fixed::operator*(const Fixed &fixed) const {
	Fixed	result;

	result.setRawBits((this->_raw * fixed._raw) >> this->_fract);
	return (result);
}

Fixed	Fixed::operator/(const Fixed &fixed) const {
	Fixed	result;
	
	result.setRawBits((this->_raw << this->_fract) / fixed._raw);
	return (result);
}

	// ----- Incrementation ----- // 
Fixed&	Fixed::operator++() {
	this->_raw++;
	return (*this);
}

Fixed	Fixed::operator++(int) {
	Fixed	prev = *this;
	this->_raw++;
	return (prev);
}

Fixed&	Fixed::operator--() {
	this->_raw--;
	return (*this);
}

Fixed	Fixed::operator--(int) {
	Fixed	prev = *this;
	this->_raw--;
	return (prev);
}

	// ----- Extrems ----- //
Fixed&	Fixed::min(Fixed& a, Fixed& b) {
	if (a < b)
		return (a);
	else
		return (b);
}

const Fixed&	Fixed::min(const Fixed& a, const Fixed& b) {
	if (a < b)
		return (a);
	else
		return (b);
}

Fixed&	Fixed::max(Fixed& a, Fixed& b) {
	if (a > b)
		return (a);
	else
		return (b);
}

const Fixed&	Fixed::max(const Fixed& a, const Fixed& b) {
	if (a > b)
		return (a);
	else
		return (b);
}