/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:49:13 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:23:06 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB {
private:
	std::string	name;
	Weapon		*weapon;

public:
	HumanB(std::string name);
	~HumanB();

	void	attack(void);
	void	setWeapon(Weapon &_weapon);
};

#endif