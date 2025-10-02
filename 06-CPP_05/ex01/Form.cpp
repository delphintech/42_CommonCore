/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:46:22 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/15 17:04:51 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : _name("draft"), _signed(false), _signGrade(150), _execGrade(150) {}

Form::Form(std::string name, bool signe, int signGrade, int execGrade)
	: _name(name), _signed(signe), _signGrade(signGrade), _execGrade(execGrade) {
	if (_signGrade > 150 || _execGrade > 150)
		throw Form::GradeTooLowException("Grade too low (must be between 1 and 150)");
	else if (_signGrade < 1 || _execGrade < 1)
		throw Form::GradeTooHighException("Grade too high (must be between 1 and 150)");
}

Form::Form(const Form& model)
	: _name(model._name), _signed(model._signed), _signGrade(model._signGrade), _execGrade(model._execGrade) {}

Form& Form::operator=(const Form& model) { 
	this->_signed = model._signed;
	return (*this);
}

Form::~Form() {}

/********** Getters **********/
std::string	Form::getName() const { return (this->_name); }
bool		Form::getSigned() const { return (this->_signed); }
int			Form::getSignGrade() const { return (this->_signGrade); }
int			Form::getExecGrade() const { return (this->_execGrade); }

/***** Exceptions ******/
Form::GradeTooLowException::GradeTooLowException(std::string msg)
	: std::invalid_argument(msg) {}

Form::GradeTooHighException::GradeTooHighException(std::string msg)
	: std::invalid_argument(msg) {}

std::ostream& operator<<(std::ostream& os, const Form& form) {

	std::cout << COLOR(93) <<  "📃 " << form.getName();
	std::cout << "  : signing autorization [" << form.getSignGrade();
	std::cout << "], execution autorization [" << form.getExecGrade();
	std::cout << "], Signed ? [" << (form.getSigned() ? "x]" : " ]");
	std::cout << COLOR(0) << std::endl;
	return (os);
}

/********** Functions **********/
Form&	Form::beSigned(Bureaucrat& bcrat) {
	if (bcrat.getGrade() <= this->_signGrade)
		this->_signed = true;
	else 
		throw Form::GradeTooLowException("Unauthorized bureaucrat.");
	return (*this);
}