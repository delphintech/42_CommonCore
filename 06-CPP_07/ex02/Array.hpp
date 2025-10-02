/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:29:18 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 18:37:07 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

#define COLOR(nb) "\e["#nb"m"

template <typename T> class Array {
private:
	T		*_ptr;
	size_t	_size;

public:
/********** Canonical form **********/
	Array();
	Array(uint n);
	Array(Array& arr);
	Array& operator=(Array& arr);
	~Array();

/********** Function **********/
	T&		operator[](int idx);
	size_t	size();
};

#include "Array.tpp"

#endif
