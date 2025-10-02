/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationAForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:43 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/15 17:04:51 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include "fstream"

class ShrubberyCreationForm : public AForm
{
private:
	std::string			_target;
	static std::string	_tree[35];
	
public:
/********** Canonical Form**********/
	ShrubberyCreationForm();
	ShrubberyCreationForm(std::string	target);
	ShrubberyCreationForm(const ShrubberyCreationForm& form);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& form);
	~ShrubberyCreationForm();

/********** Function **********/
	void	execute(Bureaucrat const & executor) const;
};

#endif
