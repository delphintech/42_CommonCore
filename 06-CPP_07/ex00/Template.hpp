/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Template.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:45:27 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 17:19:53 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include <iostream>

#define COLOR(nb) "\e["#nb"m"

template <typename T> void swap(T &x, T &y) {
	T	swap;

	swap = x;
	x = y;
	y = swap;
}

template <typename T> T	min(T x, T y) {
	if (x == y)
		return (y);
	else if (x < y)
		return (x);
	else
		return (y);
}

template <typename T> T	max(T x, T y) {
	if (x == y)
		return (y);
	else if (x > y)
		return (x);
	else
		return (y);
}

#endif
