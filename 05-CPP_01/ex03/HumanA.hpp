/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:24:35 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/11 10:29:07 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanA {
private:
	std::string	name;
	Weapon&		weapon;

public:
	HumanA(std::string _name, Weapon& _weapon);
	~HumanA();

	void	attack(void);
};

#endif