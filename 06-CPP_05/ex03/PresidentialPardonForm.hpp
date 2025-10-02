/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:29 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/16 09:22:22 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
	std::string	_target;
	
public:
/********** Canonical Form**********/
	PresidentialPardonForm();
	PresidentialPardonForm(std::string	target);
	PresidentialPardonForm(const PresidentialPardonForm& form);
	PresidentialPardonForm& operator=(const PresidentialPardonForm& form);
	~PresidentialPardonForm();

/********** Function **********/
	void	execute(Bureaucrat const & executor) const;
};

#endif