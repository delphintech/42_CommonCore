/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:24:55 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 12:25:55 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
#include "Contact.hpp"
#include "PhoneBook.hpp"

void	pretty_print(std::string str, std::string color)
{
	int	i;

	i = 0;
	std::cout << color << std::flush;
	while (str[i])
	{
		std::cout << str[i] << std::flush;
		usleep(50000);
		i++;
	}
	std::cout << "\e[0m" << std::endl;
}

int	main(void)
{
	std::string	buff;
	Phonebook		phonebook;

	std::cout << std::endl;
	pretty_print("📠 Welcome to your shitty Phonebook 📠", "\e[1;35;46m");
	while (1)
	{
		std::cout << std::endl;
		pretty_print("What do you want to do ?", "\e[3;36m");
		std::cout << "> ";
		std::cin >> buff;
		if (!buff.compare("exit"))
			break;
		else if (!buff.compare("add"))
			phonebook.Add();
		else if (!buff.compare("search"))
			phonebook.Search();
		else
			pretty_print("😡 BAD INPUT", "\e[3;36m");
	}
	std::cout << std::endl;
	pretty_print("Ok ! Bye bye ! 👋", "\e[1;35;46m");
}
