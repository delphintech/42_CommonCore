/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:34:25 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/15 17:04:51 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
	const std::string	_name;
	bool				_signed;
	const int			_signGrade;
	const int			_execGrade;
	
public:
	/********** Cannonical form **********/
	Form();
	Form(std::string name, bool signe, int signGrade, int execGrade);
	Form(const Form& model);
	Form& operator=(const Form& model);
	~Form();

	/********** Getters **********/
	std::string	getName() const;
	bool		getSigned() const;
	int			getSignGrade() const;
	int			getExecGrade() const;

	/********** Functions **********/
	Form&	beSigned(Bureaucrat& bcrat);

	/********** Exceptions **********/
	class GradeTooHighException : public std::invalid_argument {
	public:
		GradeTooHighException(std::string msg);
	};

	class GradeTooLowException : public std::invalid_argument {
	public:
		GradeTooLowException(std::string msg);
	};
};

std::ostream &operator<<(std::ostream& os, const Form& form);

#endif
