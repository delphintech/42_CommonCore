/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:40:19 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/16 15:03:30 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "AForm.hpp"

#define COLOR(nb) "\e["#nb"m"

class AForm;

class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;
	
public:
/********** Canonical form **********/
	Bureaucrat();
	Bureaucrat(std::string _name, int grade);
	Bureaucrat(const Bureaucrat& model);
	Bureaucrat& operator=(const Bureaucrat& model);
	~Bureaucrat();
	
	/********** Functions **********/
	Bureaucrat&			upGrade();
	Bureaucrat&			downGrade();
	Bureaucrat&			signForm(AForm& form);
	Bureaucrat&			executeForm(AForm const & form);

	/********** Getters **********/
	const std::string&	getName() const;
	int					getGrade() const;

	/********** Exceptions **********/
	class GradeTooHighException : public std::invalid_argument {
	public:
		GradeTooHighException();
	};

	class GradeTooLowException : public std::invalid_argument {
	public:
		GradeTooLowException();
	};
};

std::ostream &operator<<(std::ostream& os, const Bureaucrat& bcrat);

#endif

