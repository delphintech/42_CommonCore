/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:56:02 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/15 17:04:51 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void) {
	// Create 2 bureaucrats
	Bureaucrat	lea("Lea", 5);
	Bureaucrat	bob("Bob", 100);

	// Try to create a form with bas parameters
	try {
		Form	bad("bad", false, 0, 32);
	}
	catch (std::exception& e) {
		std::cout << "🚨 Bad Form: " << e.what() << std::endl;
	}

	// Create 2 forms
	Form	contract("Contract", false, 50, 50);
	Form	bill("Bill", false, 120, 120);

	std::cout << contract << bill;
	
	// Try to create a form with bas parameters
	bob.signForm(bill);
	bob.signForm(contract);

	std::cout << contract << bill;
	lea.signForm(contract);
	std::cout << contract << bill;
}