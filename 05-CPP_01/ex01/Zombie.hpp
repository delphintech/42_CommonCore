/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:29:54 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:22:47 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie {

private:
	std::string	name;
	
public:
	Zombie();
	Zombie(std::string params);
	~Zombie(void);
	
	void announce(void);
	void setName(std::string name);
};

#endif