/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:41:27 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/10 17:29:41 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Transforme une string en int
int	toInt(char* str) {
	int	i = 0;

	while (str[i]) {
		if (!std::isdigit(str[i]))
			return (-1);
		i++;
	}
	int	nb = std::atoi(str);
	if (std::strlen(str) >= 10 && nb < 1000000000)
		return (-1);
	return (nb);
}

// Donne le n nombre de la suite Jacobstal commençant par 2
int jacobstal(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return (2);
    return (jacobstal(n - 1) + 2 * jacobstal(n - 2));
}
