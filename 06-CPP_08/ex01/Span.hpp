/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:43:04 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/22 16:25:47 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <exception>
#include <cstdlib>

#define COLOR(nb) "\e["#nb"m"

class Span
{
private:
	std::vector<int>	_list;
	size_t				_size;

public:
/********** Canonical form **********/
	Span();
	Span(uint n);
	Span(Span& span);
	Span operator=(Span& span);
	~Span();

/********** Functions **********/
	void		addNumber(int nb);
	void		fillRandom(size_t size);
	uint		shortestSpan();
	uint		longestSpan();


	std::vector<int>&	getList();
};

#endif
