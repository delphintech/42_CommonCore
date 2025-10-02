/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:27:29 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:23:17 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon {
private:
	std::string	type;
	
public:
	Weapon(std::string type);
	~Weapon();

	const std::string&	getType(void);
	void				setType(std::string type);
};

#endif