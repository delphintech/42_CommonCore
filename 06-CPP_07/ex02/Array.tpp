/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:47:43 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 18:49:21 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

/********** Canonical form **********/
template <typename T> Array<T>::Array() : _ptr(NULL), _size(0) {}

template <typename T> Array<T>::Array(uint n) {
	_ptr = new T[n];
	_size = n;
}

template <typename T> Array<T>::Array(Array<T>& arr) : _size(arr._size) {
	_ptr = new T[_size];
	for (size_t i = 0; i < _size; i++) {
		_ptr[i] = arr._ptr[i];
	}
}

template <typename T> Array<T>& Array<T>::operator=(Array<T>& arr) {
	if (this == &arr)
		return (*this);
	delete[] this->_ptr;
	this->_size = arr.size();
	this->_ptr = new T[this->_size];
	for (size_t i = 0; i < this->_size; i++) {
		this->_ptr[i] = arr._ptr[i];
	}
	return (*this);
}

template <typename T> Array<T>::~Array() {
	delete[] _ptr;
}

/********** Function **********/
template <typename T> T&	Array<T>::operator[](int idx) {
	if (idx >= (int)this->_size || idx < 0)
        throw std::out_of_range("Index out of array limit");
	return (this->_ptr[idx]);
}

template <typename T> size_t	Array<T>::size() { return (this->_size); }
