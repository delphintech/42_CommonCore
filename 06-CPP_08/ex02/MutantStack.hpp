/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:42 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/23 14:36:05 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <stack>

#define COLOR(nb) "\e["#nb"m"

template <typename T> class MutantStack : public std::stack<T> {
public:
/********** Canonical formn **********/
	MutantStack();
	MutantStack(MutantStack& stack);
	MutantStack& operator=(MutantStack& stack);
	~MutantStack();

/********** iterators **********/
	typedef typename std::stack<T>::container_type::iterator				iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator		reverse_iterator;
	typedef typename std::stack<T>::container_type::const_iterator			const_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;


/********** Functions **********/
	iterator 				begin();
	iterator		 		end();
	reverse_iterator		rbegin();
	reverse_iterator		rend();
	const_iterator			cbegin() const;
	const_iterator			cend() const;
	const_reverse_iterator	crbegin() const;
	const_reverse_iterator	crend() const;
};

#include "MutantStack.tpp"

#endif
