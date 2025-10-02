/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:10:20 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/22 14:38:08 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>

#define COLOR(nb) "\e["#nb"m"

template <typename T> typename T::iterator easyfind(T& container, int n) {
	typename T::iterator	result(container.end());

	result = std::find(container.begin(), container.end(), n);
	if (result == container.end())
		throw n;
	return (result);
}

#endif
