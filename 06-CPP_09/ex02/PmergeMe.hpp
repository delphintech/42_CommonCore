/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:04:44 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/10 17:31:19 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iomanip>

int		toInt(char* str);
int		jacobstal(int n);

template <template <typename, typename> class Cont>
bool	test(Cont<int, std::allocator<int> > cont);

template <template <typename, typename> class Cont>
class PmergeMe {
private:
	typedef	Cont<int, std::allocator<int> >	Container;
	typedef typename Container::iterator	Iterator;
    Container _cont;

public:
/********** Canonical form **********/
	PmergeMe();
	PmergeMe(int ac, char **av);
	PmergeMe(const PmergeMe& model);
	PmergeMe& operator=(const PmergeMe& model);
	~PmergeMe();

/********** Static **********/
static Iterator	getIt(Container& cont, int pos);

/********** Utils **********/
int			getSize();
void		display();
bool		test();
void		moveTo(int start, int size, Container& receiver, int pos);

/********** Algo **********/
int			sortPairs(int level);
Iterator	binarySearch(Iterator start, Iterator end, int value, bool pair);
void		mergeInsert(Container *main, int level, bool pair);
void		fordJohnson();
};

#include "PmergeMe.tpp"

#endif
