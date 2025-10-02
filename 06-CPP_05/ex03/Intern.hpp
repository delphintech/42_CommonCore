/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:34:17 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/17 10:47:32 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include <cstring>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
public:
/********** Canonical form **********/
	Intern();
	Intern(const Intern& model);
	Intern& operator=(const Intern& model);
	~Intern();

/********** Functions **********/
	static AForm	*makeShrubbery(std::string target);
	static AForm	*makeRobotomy(std::string target);
	static AForm	*makePresidential(std::string target);
	static AForm	*makeForm(std::string name, std::string target);

/********** Exception **********/
class InvalidNameException : public std::invalid_argument {
	public:
		InvalidNameException(std::string msg);
};
};

#endif