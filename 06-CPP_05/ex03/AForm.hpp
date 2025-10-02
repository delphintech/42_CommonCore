/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:34:25 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/17 11:11:10 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
private:
	const std::string	_name;
	bool				_signed;
	const int			_signGrade;
	const int			_execGrade;
	
public:
	/********** Cannonical form **********/
	AForm();
	AForm(std::string name, bool signe, int signGrade, int execGrade);
	AForm(const AForm& model);
	AForm& operator=(const AForm& model);
	virtual ~AForm();

	/********** Getters **********/
	std::string	getName() const;
	bool		getSigned() const;
	int			getSignGrade() const;
	int			getExecGrade() const;

	/********** Functions **********/
	AForm&	beSigned(Bureaucrat& bcrat);
	bool	is_executable(const Bureaucrat & bcrat) const;
	virtual void	execute(Bureaucrat const & executor) const = 0;

	/********** Exceptions **********/
	class GradeTooHighException : public std::invalid_argument {
	public:
		GradeTooHighException(std::string msg);
	};

	class GradeTooLowException : public std::invalid_argument {
	public:
		GradeTooLowException(std::string msg);
	};

	class UnisgnedException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

std::ostream &operator<<(std::ostream& os, const AForm& form);

#endif
