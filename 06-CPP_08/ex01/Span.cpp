/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:43:41 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/22 16:31:44 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

/********** Canonical form **********/
Span::Span() : _size(0) {
	_list.reserve(0);
}

Span::Span(uint n) : _size(n) {
	_list.reserve(n);
}

Span::Span(Span& span)  : _size(span._size) {
	_list.reserve(_size);
}

Span Span::operator=(Span& span) {
	if (this == &span)
		return (*this);

	this->_list.clear();
	this->_size = span._size;
	this->_list.reserve(span._size);
	return (*this);
}

Span::~Span() { this->_list.clear(); }

/********** Functions **********/
void		Span::addNumber(int nb) {
	if (this->_list.size() >= this->_size)
		throw std::logic_error("The list is full");
	this->_list.push_back(nb);
}

int	randomNumber() { return (std::rand() % 1000000); }

void		Span::fillRandom(size_t size) {
	if (this->_list.size() + size > this->_size)
		throw std::logic_error("List too small");
	this->_list.resize(this->_list.size() + size);
	std::generate_n(this->_list.begin(), size, randomNumber);
}

uint		Span::shortestSpan() {
	uint	span;

	if (this->_size < 2)
		throw std::logic_error("List too small");
	std::sort(this->_list.begin(), this->_list.end());
	span = this->longestSpan();
	for (size_t i = 0; i < this->_size; i++) {
		if (i != 0 && std::abs(this->_list.at(i) - this->_list.at(i - 1)) < span)
			span = std::abs(this->_list.at(i) - this->_list.at(i - 1));
	}
	return (span);
}

uint		Span::longestSpan() {
	uint	span;

	if (this->_size < 2)
		throw std::logic_error("List too small");
	span = *std::max_element(this->_list.begin(), this->_list.end())
		- *std::min_element(this->_list.begin(), this->_list.end());
	return (span);
	}


std::vector<int>&	Span::getList() { return (this->_list); }
