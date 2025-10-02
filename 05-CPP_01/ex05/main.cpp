/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:07:14 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/28 12:55:19 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Harl.hpp"

int	main()
{
	Harl	harl;

	std::cout << "DEBUG ..." << std::endl;
	harl.complain("DEBUG");
	std::cout << "INFO ..." << std::endl;
	harl.complain("INFO");
	std::cout << "WARNING ..." << std::endl;
	harl.complain("WARNING");
	std::cout << "ERROR ..." << std::endl;
	harl.complain("ERROR");
}