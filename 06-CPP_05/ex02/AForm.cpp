/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:46:22 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/15 17:04:51 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() : _name("draft"), _signed(false), _signGrade(150), _execGrade(150) {}

AForm::AForm(std::string name, bool signe, int signGrade, int execGrade)
	: _name(name), _signed(signe), _signGrade(signGrade), _execGrade(execGrade) {
	if (_signGrade > 150 || _execGrade > 150)
		throw AForm::GradeTooLowException("Grade too low (must be between 1 and 150)");
	else if (_signGrade < 1 || _execGrade < 1)
		throw AForm::GradeTooHighException("Grade too high (must be between 1 and 150)");
}

AForm::AForm(const AForm& model)
	: _name(model._name), _signed(model._signed), _signGrade(model._signGrade), _execGrade(model._execGrade) {}

AForm& AForm::operator=(const AForm& model) { 
	this->_signed = model._signed;
	return (*this);
}

AForm::~AForm() {}

/********** Getters **********/
std::string	AForm::getName() const { return (this->_name); }
bool		AForm::getSigned() const { return (this->_signed); }
int			AForm::getSignGrade() const { return (this->_signGrade); }
int			AForm::getExecGrade() const { return (this->_execGrade); }

/***** Exceptions ******/
AForm::GradeTooLowException::GradeTooLowException(std::string msg)
	: std::invalid_argument(msg) {}

AForm::GradeTooHighException::GradeTooHighException(std::string msg)
	: std::invalid_argument(msg) {}

const char	*AForm::UnisgnedException::what() const throw() { return ("Unisigned Document!");}

std::ostream& operator<<(std::ostream& os, const AForm& form) {

	std::cout << COLOR(93) <<  "📃 " << form.getName();
	std::cout << "  : signing autorization [" << form.getSignGrade();
	std::cout << "], execution autorization [" << form.getExecGrade();
	std::cout << "], Signed ? [" << (form.getSigned() ? "x]" : " ]");
	std::cout << COLOR(0) << std::endl;
	return (os);
}

/********** Functions **********/
AForm&	AForm::beSigned(Bureaucrat& bcrat) {
	if (bcrat.getGrade() <= this->_signGrade)
		this->_signed = true;
	else 
		throw AForm::GradeTooLowException("Unauthorized bureaucrat.");
	return (*this);
}

bool	AForm::is_executable(const Bureaucrat& bcrat) const {
	if (this->_signed && bcrat.getGrade() <= this->_execGrade)
		return (true);
	else if (bcrat.getGrade() > this->_execGrade)
		throw AForm::GradeTooLowException("Unauthorized bureaucrat.");
	else
		throw AForm::UnisgnedException();
	return (false);
}