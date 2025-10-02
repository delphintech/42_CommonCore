/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:17:56 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/16 11:35:03 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>

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