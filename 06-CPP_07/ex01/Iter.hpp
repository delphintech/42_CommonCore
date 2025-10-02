/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:09:16 by dabouab           #+#    #+#             */
/*   Updated: 2025/03/19 15:30:48 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

#define COLOR(nb) "\e["#nb"m"

template <typename T, typename F> void	iter(T array[], size_t	arr_size, F(T)) {
	for (size_t i = 0; i < arr_size; i++) {
		f(array[i]);
	}
}

template <typename T> void display(T var) {
	std::cout << var << std::endl;
}

#endif
