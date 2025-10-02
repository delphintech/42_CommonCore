/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:41:53 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/23 14:35:58 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

/********** Canonical form **********/
template <typename T> MutantStack<T>::MutantStack() : std::stack<T>() {}

template <typename T> MutantStack<T>::MutantStack(MutantStack& stack) : std::stack<T>(stack) {}

template <typename T> MutantStack<T>&  MutantStack<T>::operator=(MutantStack& stack) {
	std::stack<T>::operator=(stack);
	return (*this);
}

template <typename T> MutantStack<T>::~MutantStack() {}

/********** Functions **********/
template <typename T> typename MutantStack<T>::iterator 				MutantStack<T>::begin() { return (this->c.begin()); }
template <typename T> typename MutantStack<T>::iterator		 			MutantStack<T>::end() { return (this->c.end()); }
template <typename T> typename MutantStack<T>::reverse_iterator			MutantStack<T>::rbegin() { return (this->c.rbegin()); }
template <typename T> typename MutantStack<T>::reverse_iterator			MutantStack<T>::rend() { return (this->c.rend()); }
template <typename T> typename MutantStack<T>::const_iterator			MutantStack<T>::cbegin() const { return (this->c.cbegin()); }
template <typename T> typename MutantStack<T>::const_iterator			MutantStack<T>::cend() const { return (this->c.cend()); }
template <typename T> typename MutantStack<T>::const_reverse_iterator	MutantStack<T>::crbegin() const { return (this->c.crbegin()); }
template <typename T> typename MutantStack<T>::const_reverse_iterator	MutantStack<T>::crend() const { return (this->c.crend()); }
