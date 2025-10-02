/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:28:46 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/28 17:26:57 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

void	error() {
	std::cout << "Error" << std::endl;
}

int	main(int ac, char **av) {
	if (ac != 2)
		return (error(), 1);

	RPN		rpn(av[1]);
		
	int	result = rpn.total();
	if (result < 0)
		return (error(), 1);
	std::cout << result << std::endl;
	return (0);
}
