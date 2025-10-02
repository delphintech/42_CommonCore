/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:16:06 by dabouab           #+#    #+#             */
/*   Updated: 2025/03/20 13:08:31 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/********** Canonical form **********/
template <template <typename, typename> class Cont>
PmergeMe<Cont>::PmergeMe() {}

template <template <typename, typename> class Cont>
PmergeMe<Cont>::PmergeMe(int ac, char **av) {
	std::string	params;;
	int		i = 1;
	char	*word;
	int		nb;

	while (i < ac) {
		params = av[i];
		word = std::strtok(const_cast<char*>(params.c_str()), " ");
		while (word != NULL) {
			nb = toInt(word);
			if (nb < 0 || std::find(_cont.begin(), _cont.end(), nb) != _cont.end()) {
				_cont.clear();
				break ;
			}
			else
				_cont.push_back(nb);
			word = std::strtok(NULL, " ");
		}
		i++;
	}
}

template <template <typename, typename> class Cont>
PmergeMe<Cont>::PmergeMe(const PmergeMe& model) : _cont(model._cont) {}

template <template <typename, typename> class Cont>
PmergeMe<Cont>& PmergeMe<Cont>::operator=(const PmergeMe<Cont>& model) {
	if (this == &model)
		return (*this);
	this->_cont.clear();
	this->_cont = model._cont;
	return (*this);
}

template <template <typename, typename> class Cont>
PmergeMe<Cont>::~PmergeMe() { _cont.clear(); }

/********** Static **********/

// getIt - Retourne l'iterateur de la position voulue
template <template <typename, typename> class Cont>
typename PmergeMe<Cont>::Iterator	PmergeMe<Cont>::getIt(Container& cont, int pos) {
	Iterator	it = cont.begin();

	if (pos < 0)
		return (cont.begin());
	if (pos > static_cast<int>(cont.size()))
		return (cont.end());
	std::advance(it, pos);
    return (it);
}

/********** Utils **********/
// getSize
template <template <typename, typename> class Cont>
int		PmergeMe<Cont>::getSize() { return (static_cast<int>(this->_cont.size())); }

// Display
template <template <typename, typename> class Cont>
void		PmergeMe<Cont>::display() {
	Iterator	it;

	for (it = this->_cont.begin(); it != this->_cont.end(); it++) {
		if (it != this->_cont.begin())
			std::cout << " ";
		std::cout << *it;
	}
	std::cout << std::endl;
}

template <template <typename, typename> class Cont>
void		PmergeMe<Cont>::moveTo(int start, int size, Container& receiver, int pos) {

	receiver.insert(getIt(receiver, pos), getIt(this->_cont, start), getIt(this->_cont, start + size));
	this->_cont.erase(getIt(this->_cont, start), getIt(this->_cont, start + size));
}

/********** Algo **********/

// Algorithhm de tri par paires
template <template <typename, typename> class Cont>
int		PmergeMe<Cont>::sortPairs(int level) {
	int step = std::pow(2, level);
	int i = step - 1;
	Iterator a;
	Iterator b;

	if (step > (static_cast<int>(this->_cont.size()) / 2)) {
		return (step / 2);
	}
	while (i < static_cast<int>(this->_cont.size())) {
		a = getIt(this->_cont, i);
		b = getIt(this->_cont, i + step);
		if (a != this->_cont.end() && b != this->_cont.end() && *a > *b)
			std::swap_ranges(getIt(this->_cont, i - step + 1), ++a, a);
		i += 2 * step;
	}
	return (sortPairs(++level));
}

// Renvoie l'index oú insérer la value
template <template <typename, typename> class Cont>
typename PmergeMe<Cont>::Iterator	PmergeMe<Cont>::binarySearch(PmergeMe<Cont>::Iterator start, PmergeMe<Cont>::Iterator end, int value, bool pair) {
	Iterator	test;
	Iterator	base = start;

	while (std::distance(start, end) > (pair ? 2 : 1)) {
		test = start;
		std::advance(test, std::distance(start, end) / 2);

		if (pair && std::distance(base, test) % 2 == 0) {
            if (test != end)
                ++test;
            else
                --test;
        }

		if (value < *test)
			end = test;
		else
			start = test;
	}
	if (value < *start)
		return (start);
	if (value > *end)
		return (++end);
	return (end);
}

// Merge insert grâce au binary search en suivant le suite de Jacobstal
template <template <typename, typename> class Cont>
void		PmergeMe<Cont>::mergeInsert(Container *main, int level, bool pair) {
	int	jacob = jacobstal(level);
	Iterator	pend;
	Iterator	pos;

	if (pair)
		jacob *= 2;
	if (jacob > static_cast<int>(this->_cont.size())) {
		jacob = static_cast<int>(this->_cont.size());
		if (pair && jacob % 2 == 1)
			jacob--;
	}
	while (jacob > 0) {
		pend = getIt(this->_cont, jacob - 1);
		pos = binarySearch(main->begin(), main->end(), *pend, pair);
		if (pair) {
			pend--;
			if (pos == main->end())
				pos--;
			pos--;
		}
		this->moveTo(std::distance(this->_cont.begin(), pend), pair ? 2 : 1, *main, std::distance(main->begin(), pos));
		jacob--;
		if (pair)
			jacob--;
	}
	if (this->_cont.size() >= (pair ? 2 : 1))
		mergeInsert(main, ++level, pair);
}

// Agorithme complet de Ford-Johnson
template <template <typename, typename> class Cont>
void		PmergeMe<Cont>::fordJohnson() {
	int			step;
	Container	main;

	// Pair sort
	step = this->sortPairs(0);

	// Initialise avec 3 paires (a1, a2 et b2)
	if (step > 4)
		this->moveTo(2 * step - 2, 2, main, 0);
	if (step > 2)
		this->moveTo(step - 2, 2, main, 0);
	this->moveTo(0, 2, main, 0);

	// Tri des paires avec merge insert
	this->mergeInsert(&main, 1, true);

	// On garde les nombres les plus grands triés
	int			i = 0;
	Iterator	it;
	while (i < static_cast<int>(main.size())) {
		it = getIt(main, i);
		this->_cont.push_back(*it);
		main.erase(it);
		i++;
	}

	// On insert le reste grâce à merge-insert
	this->mergeInsert(&main, 1, false);

	// on rend la liste triée au container
	this->_cont = main;
}

// Test
template <template <typename, typename> class Cont>
bool	PmergeMe<Cont>::test() {
	for (Iterator it = this->_cont.begin(); it != this->_cont.end() - 1; ++it) {
        if (*it > *(it + 1)) {
			std::cout << "💀" << std::endl;
			return (false);
        }
    }
	std::cout << "✅" << std::endl;
	return (true);
}