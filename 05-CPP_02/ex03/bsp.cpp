/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:45:43 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:16:03 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	a_test;
	Fixed	b_test;
	Fixed	c_test;

	a_test = a.vector(point) * a.vector(b);
	b_test = b.vector(point) * b.vector(c);
	c_test = c.vector(point) * c.vector(a);
	
	if (a_test == 0 || b_test == 0 || c_test == 0)
		return (false);
	else if (a_test > 0 && b_test > 0 && c_test > 0)
		return (true);
	else if (a_test < 0 && b_test < 0 && c_test < 0)
		return (true);
	return (false);
}