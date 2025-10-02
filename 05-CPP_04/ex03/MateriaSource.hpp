/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:46:58 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/11 13:52:54 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

#include <iostream>
#include "IMateriaSource.hpp"

class MateriaSource : virtual public IMateriaSource
{
private:
	AMateria	*_inventory[4];

public:
	MateriaSource();
	MateriaSource(const MateriaSource &arg);
	MateriaSource& operator=(const MateriaSource &arg);
	~MateriaSource();
	
	void learnMateria(AMateria*);
	AMateria* createMateria(std::string const & type);
};

#endif