/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:45:46 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:27:14 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include <iostream>
#include "Fixed.hpp"

class Point {
private:
	const Fixed	_x;
	const Fixed	_y;
	
public:
	Point();
	Point(const float x, const float y);
	Point(const Point& point);
	Point& operator=(const Point& point);
	~Point();

	const Fixed		getX() const;
	const Fixed		getY() const;

	const Point vector(const Point& point) const;
	Fixed	operator*(const Point& point) const;
};

#endif