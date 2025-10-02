/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:00:07 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/04 11:51:59 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() {};

Point::Point(const float x, const float y) : _x(x), _y(y) {};

Point::Point(const Point& point) : _x(point._x), _y(point._y) {};

Point& Point::operator=(const Point& point) {
	(void)point;
	return (*this);
};

Point::~Point() {};

const Fixed		Point::getX() const {
	return (this->_x);
}
const Fixed		Point::getY() const {
	return (this->_y);
}

const Point Point::vector(const Point& point) const
{
	Point	vector((point._x - this->_x).toFloat(), 
		(point._y - this->_y).toFloat());
	return (vector);
}

Fixed	Point::operator*(const Point& point) const
{
	Fixed	result;

	result = point._x * this->_y - this->_x * point._y;
	return (result);
}