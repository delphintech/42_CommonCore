/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:17:56 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/17 11:36:56 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
private:
	std::string	_target;
	
public:
/********** Canonical Form**********/
	RobotomyRequestForm();
	RobotomyRequestForm(std::string	target);
	RobotomyRequestForm(const RobotomyRequestForm& form);
	RobotomyRequestForm& operator=(const RobotomyRequestForm& form);
	~RobotomyRequestForm();

/********** Function **********/
	void	execute(Bureaucrat const & executor) const;
};

#endif