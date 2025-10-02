/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:46:04 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 12:24:58 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

Phonebook::Phonebook() {
}

Phonebook::~Phonebook() {
}

int	Phonebook::Display() {
	int	i;

	if (!this->list[0].getPhone().compare(""))
	{
		pretty_print("---------Your Phonebook is empty !----------", "\e[3;36m");
		return (0);
	}

	std::cout << "---------------------------------------------\n";
	std::cout << "|     index|first name| last name|  nickname|\n";
	std::cout << "---------------------------------------------\n";

	i = 0;
	while (i < 8 && this->list[i].getPhone().compare(""))
	{
		this->list[i].SearchDisplay(i + 1);
		i++;
	}
	return (i);
}

void	Phonebook::Search() {
	int i;
	int	buf;

	i = this->Display();
	if (i == 0)
		return ;
	pretty_print("Which contact do you want to display ?", "\e[3;36m");
	std::cout << "> ";
	std::cin >> buf;
	while (buf <= 0 || buf > i)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		pretty_print("😡 Please select a valid index !", "\e[3;36m");
		std::cout << "> ";
		std::cin >> buf;
	}
	this->list[buf - 1].FullDisplay();
}

void	Phonebook::Add() {
	int	nb;
	int	i;

	nb = 0;
	while (nb < 8 && this->list[nb].getPhone().compare(""))
		nb++;
	i = nb - 1;
	while (i >= 0)
	{
		if (i + 1 < 8)
			this->list[i + 1] = this->list[i];
		i--;
	}
	this->list[0].Add();
}
