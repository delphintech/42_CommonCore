/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:33:25 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 14:18:36 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string params){
	name = params;
}

Zombie::Zombie(void){
	name = "";
}

Zombie::~Zombie(void) {
	std::cout << "RIP " << this->name << " 💀" << std::endl;
}
	
void Zombie::announce(void) {
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string params) {
	this->name = params;
}