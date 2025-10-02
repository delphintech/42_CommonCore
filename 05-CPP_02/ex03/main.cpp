/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:31:40 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/04 11:56:46 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"
#include "Point.hpp"

bool	bsp( Point const a, Point const b, Point const c, Point const point);

void	blue_print(std::string str) {
	std::cout << "\e[34m" << str << "\e[0m" << std::endl;
}

void	print_result(Point point, bool result)
{
	std::cout << "The point (" << point.getX() << ", " << point.getY() << ") ";
	if (result)
		std::cout << "is INSIDE the triangle." << std::endl;
	else
		std::cout << "is OUTSIDE the triangle." << std::endl;
}

int	main (void)
{
	const Point	a = Point(0, 0);
	const Point	b = Point(0, 10);
	const Point	c = Point(20, 0);
	bool	result;

	blue_print("inside the triangle");
	result  = bsp(a, b, c, Point(7.56, 3.21));
	print_result(Point(7.56, 3.21), result);
	
	blue_print("outside the triangle");
	result  = bsp(a, b, c, Point(25, 5.65));
	print_result(Point(25, 5.65), result);
	
	blue_print("In a vertex");
	result  = bsp(a, b, c, Point(20, 0));
	print_result(Point(20, 0), result);
	
	blue_print("In an edge");
	result  = bsp(a, b, c, Point(0, 5));
	print_result(Point(0, 5), result);
}