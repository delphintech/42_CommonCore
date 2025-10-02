/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:17:43 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/16 13:35:12 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

// Required grades: sign 72, exec 45
// Makes some drilling noises. Then, informs that <target> has been robotomized
// successfully 50% of the time. Otherwise, informs that the robotomy failed.

/********** Canonical Form**********/
RobotomyRequestForm::RobotomyRequestForm() 
	: AForm("RobotomyRequestForm", false, 72, 45), _target("default") {}

RobotomyRequestForm::RobotomyRequestForm(std::string target)
	: AForm("RobotomyRequestForm", false, 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& form) 
	: AForm("RobotomyRequestForm", form.getSigned(), 72, 45), _target(form._target) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& form) {
	this->AForm::operator=(form);
	this->_target =  form._target;
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {}

/********** Function **********/
void	RobotomyRequestForm::execute(Bureaucrat const & executor) const {
	if (!this->is_executable(executor))
		return ;
	
	std::cout << "🔊 ... Driiilllll ... 🔊 ... Driiilllll ..." << std::endl;
	
	int	n = std::rand() % 2;
	if (n == 0)
		std::cout << "Target '" << this->_target << "' has been robotomized 🤖 ... bip boop ..." << std::endl;
	else
		std::cout << "Robotomy failed ..." << std::endl;
}