/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:34:08 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/17 11:29:39 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

/********** Canonical form **********/
Intern::Intern() {}
Intern::Intern(const Intern& model) { (void)model; }
Intern& Intern::operator=(const Intern& model) { (void)model; return (*this);}
Intern::~Intern() {}

/********** Functions **********/
AForm	*Intern::makeShrubbery(std::string target) {
	ShrubberyCreationForm *form;
	
	form = new ShrubberyCreationForm(target);
	return (form);
}

AForm	*Intern::makeRobotomy(std::string target) {
	RobotomyRequestForm *form;
	
	form = new RobotomyRequestForm(target);
	return (form);
}

AForm	*Intern::makePresidential(std::string target) {
	PresidentialPardonForm *form;
	
	form = new PresidentialPardonForm(target);
	return (form);
}

void suppressWarnings() {
    (void)&Intern::makeShrubbery;
    (void)&Intern::makeRobotomy;
    (void)&Intern::makePresidential;
}

AForm	*Intern::makeForm(std::string name, std::string target) {
	std::string	forms[3] = {"shrubbery", "robotomy", "presidential"};
	typedef AForm* (*Func)(std::string target);
	Func		makefunc[3] = {&Intern::makeShrubbery, &Intern::makeRobotomy, &Intern::makePresidential}; 

	suppressWarnings();
	for (size_t i = 0; i < name.length(); i++) {
		name[i] = std::tolower(name[i]);
	}
	
	int i = 0;
	while (i < 3)
	{
		if (name.find(forms[i]) != std::string::npos)
			break;
		i++;
	}

	if (i < 3)
		return (makefunc[i](target));
	else
		throw InvalidNameException("'" + name + "' is not a valid form");
}

/********** Exception **********/
Intern::InvalidNameException::InvalidNameException(std::string msg) 
	: std::invalid_argument(msg) {}