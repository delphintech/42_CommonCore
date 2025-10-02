/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:56:02 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/17 11:24:59 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int	main(void) {
	Bureaucrat	lea("lea", 5);
	AForm		*form;
	
	try {
		form = Intern::makeForm("Test draft", "someone");
	}
	catch (std::exception &e) {
		std::cout << "🚨 Error: " << e.what() << std::endl;
	}
	
	std::cout << std::endl;
	form = Intern::makeForm("Robotomy request", "director");
	std::cout << *form;
	lea.signForm(*form);
	lea.executeForm(*form);
	delete	form;
	
	std::cout << std::endl;
	form = Intern::makeForm("Draft for ShruBbery", "draw");
	std::cout << *form;
	lea.signForm(*form);
	lea.executeForm(*form);
	delete	form;

	std::cout << std::endl;
	form = Intern::makeForm("Important top secret presidential", "Foreign spy");
	std::cout << *form;
	lea.signForm(*form);
	lea.executeForm(*form);
	delete	form;
	
}