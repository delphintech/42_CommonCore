/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:17 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/16 13:45:00 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

// Required grades: sign 25, exec 5
// Informs that <target> has been pardoned by Zaphod Beeblebrox.

/********** Canonical Form**********/
PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardonForm", false, 25, 5), _target("default") {}

PresidentialPardonForm::PresidentialPardonForm(std::string	target)
	: AForm("PresidentialPardonForm", false, 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& form) 
	: AForm("PresidentialPardonForm", false, 25, 5), _target(form._target) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& form) {
	this->AForm::operator=(form);
	this->_target =  form._target;
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {}

/********** Function **********/
void	PresidentialPardonForm::execute(Bureaucrat const & executor) const {
	if (!this->is_executable(executor))
		return ;
	std::cout << "'" << this->_target << "' has been pardonned by Zaphod Beeblebrox 🙏" << std::endl;
}