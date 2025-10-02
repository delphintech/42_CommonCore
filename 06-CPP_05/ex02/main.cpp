/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:56:02 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/16 15:09:25 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main(void) {
	// Create 2 bureaucrats
	Bureaucrat	lea("Lea", 5);
	Bureaucrat	bob("Bob", 100);
	Bureaucrat	john("john", 50);

	std::cout << "Bureaucrats: " << std::endl;
	std::cout << lea << bob << john << std::endl;

	// Create 4 forms
	ShrubberyCreationForm	shrubbery("Palm");
	RobotomyRequestForm		robotomy("You");
	PresidentialPardonForm	presidential("Edward Snowden");
	RobotomyRequestForm		copy = robotomy;
	
	std::cout << "Forms: " << std::endl;
	
	std::cout << shrubbery;
	bob.executeForm(shrubbery);
	bob.signForm(shrubbery);
	std::cout << shrubbery;
	john.executeForm(shrubbery);
	std::cout << std::endl;
	
	std::cout << robotomy;
	std::cout << copy;
	bob.executeForm(robotomy);
	bob.signForm(robotomy);
	john.signForm(copy);
	lea.signForm(robotomy);
	john.executeForm(robotomy);
	lea.executeForm(robotomy);
	lea.executeForm(copy);
	std::cout << std::endl;
	
	std::cout << presidential;
	lea.executeForm(presidential);
	lea.signForm(presidential);
	std::cout << presidential;
	john.executeForm(presidential);
	lea.executeForm(presidential);
}