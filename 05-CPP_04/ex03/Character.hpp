/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:23:19 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/11 16:34:12 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include <iostream>
#include "ICharacter.hpp"

class Character : virtual public ICharacter
{
private:
	std::string	_name;
	AMateria	*_inventory[4];
	
public:
	Character();
	Character(std::string arg);
	Character(const Character& arg);
	Character& operator=(const Character& arg);
	~Character();
	
	std::string const & getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);
};

#endif