/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:52 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:21:22 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

#include <iostream>
#include "ICharacter.hpp"

class ICharacter;

#define MAX_DROPS 100

class AMateria {
	
protected:
	std::string	_type;
	AMateria();

public:	
	AMateria(const std::string& type);
	AMateria(const AMateria& arg);
	AMateria& operator=(const AMateria& arg);
	virtual ~AMateria() = 0;
	
	const std::string&	getType() const;
	virtual AMateria*	clone() const = 0;
	virtual void		use(ICharacter& target) = 0;

	static	AMateria	*drops[MAX_DROPS];
	
	static void		add_drop(AMateria *materia);
	static void		take_drop(AMateria *materia);
	
};

#endif