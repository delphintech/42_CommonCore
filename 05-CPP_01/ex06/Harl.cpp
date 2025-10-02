/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:05:40 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/28 13:01:27 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(void){
	std::cout << "A wild Harl has appeared 🙋" << std::endl;
}

Harl::~Harl(void) {
	std::cout << "RIP Harl 💀" << std::endl;
}

void	Harl::debug(void) {
	std::string	str;

	str = "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!";
	std::cout << "\e[32m" << str << "\e[0m" << std:: endl;
}

void	Harl::info(void) {
	std::string	str;

	str = "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!";
	std::cout << "\e[34m" << str << "\e[0m" << std:: endl;
}

void	Harl::warning(void) {
	std::string	str;

	str = "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.";
	std::cout << "\e[33m" << str << "\e[0m" << std:: endl;
}

void	Harl::error(void) {
	std::string	str;

	str = "This is unacceptable! I want to speak to the manager now.";
	std::cout << "\e[31m" << str << "\e[0m" << std:: endl;
}

void	Harl::complain(std::string level) {
	int	i;
	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	typedef void (Harl::*Func)();
	Func	complain[4] = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	
	i = 0;
	while (i < 4)
	{
		if (!levels[i].compare(level))
			(this->*complain[i])();
		i++;
	}
}