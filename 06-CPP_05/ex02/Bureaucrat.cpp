/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:40:06 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/16 15:07:14 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Unknown"), _grade(150) {}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name) {
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else
		_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& model)
	: _name(model._name), _grade(model._grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& model) { 
	this->_grade = model._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat() {}

/***** Getters ******/
const std::string&	Bureaucrat::getName() const { return (this->_name); }
int					Bureaucrat::getGrade() const { return (this->_grade); }

/********** Functions **********/
Bureaucrat&			Bureaucrat::upGrade() {
	if (this->_grade == 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
	return (*this);
}

Bureaucrat&			Bureaucrat::downGrade() {
	if (this->_grade == 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
	return (*this);
}

Bureaucrat&				Bureaucrat::signForm(AForm& form) {
	try {
		form.beSigned(*this);
		std::cout << COLOR(34) << this->_name << " signed " 
			<< form.getName() << COLOR(0) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << this->_name << " is "<< e.what() << std::endl;
	}
	return (*this);
}

Bureaucrat&			Bureaucrat::executeForm(AForm const & form) {
	try {
		form.execute(*this);
		std::cout << COLOR(35) << this->_name << " executed "
			<< form.getName() << COLOR(0)<< std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << this->_name << ": "<< e.what() << std::endl;
	}
	return (*this);
}

/***** Exceptions ******/
Bureaucrat::GradeTooLowException::GradeTooLowException()
	: std::invalid_argument("Grade too low (must be between 1 and 150)") {}

Bureaucrat::GradeTooHighException::GradeTooHighException()
	: std::invalid_argument("Grade too high (must be between 1 and 150)") {}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bcrat) {
	std::cout << COLOR(92) << bcrat.getName() << ", bureaucrat grade ";
	std::cout << bcrat.getGrade() << "." << COLOR(0) << std::endl;
	return (os);
}