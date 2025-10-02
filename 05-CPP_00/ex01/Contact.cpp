/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:34:27 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 12:24:48 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {
	name = "";
	last_name = "";
	nickname = "";
	phone = "";
	darkest_secret = "";
}

Contact::~Contact() {
}

std::string	Contact::getPhone() {
	return this->phone;
}

bool Contact::CheckNum() {
	int	i;

	if (!this->phone.compare(""))
		return (false);
	i = 0;
	while (this->phone[i])
	{
		if (!std::isdigit(this->phone[i]))
			return (false);
		i++;
	}
	return (true);
}

void Contact::Add() {
	std::string	buff;

	pretty_print("--- New Contact --", "\e[3;36m");
	std::cout << "\e[3;36mName: \e[0m";
	std::cin.ignore();
	std::getline(std::cin, buff);
	this->name = buff;

	std::cout << "\e[3;36mLast_name: \e[0m";
	std::cin.ignore();
	std::getline(std::cin, buff);
	this->last_name = buff;

	std::cout << "\e[3;36mNickname: \e[0m";
	std::cin.ignore();
	std::getline(std::cin, buff);
	this->nickname = buff;

	std::cout << "\e[3;36mPhone: \e[0m";
	std::cin.ignore();
	std::getline(std::cin, buff);
	this->phone = buff;

	while (!this->CheckNum())
	{
		pretty_print("Enter a valid phone", "\e[3;36m");
		std::cout << "\e[3;36mPhone: \e[0m";
		std::cin.ignore();
		std::getline(std::cin, buff);
		this->phone = buff;
	}

	std::cout << "\e[3;36mDarkest secret: \e[0m";
	std::cin.ignore();
	std::getline(std::cin, buff);
	this->darkest_secret = buff;
}

void	Contact::SearchDisplay(int index) {
	std::cout << "|" << std::setw(10) << index;

	std::cout << "|";
	if (this->name.length() <= 10)
		std::cout << std::setw(10) << this->name;
	else
		std::cout.write(name.c_str(), 9) << ".";
	std::cout.flush();

	std::cout << "|";
	if (this->last_name.length() <= 10)
		std::cout << std::setw(10) << this->last_name;
	else
		std::cout.write(last_name.c_str(), 9) << ".";
	std::cout.flush();

	std::cout << "|";
	if (this->nickname.length() <= 10)
		std::cout << std::setw(10) << this->nickname;
	else
		std::cout.write(nickname.c_str(), 9) << ".";
	std::cout.flush();
	std::cout << "|\n";
	std::cout << "----------------------------------------------\n";
}

void	Contact::FullDisplay()
{
	std::cout << "\e[3;36mName: \e[0m" << this->name << std::endl;
	std::cout << "\e[3;36mLast name: \e[0m" << this->last_name << std::endl;
	std::cout << "\e[3;36mNickname: \e[0m" << this->nickname << std::endl;
	std::cout << "\e[3;36mPhone: \e[0m" << this->phone << std::endl;
	std::cout << "\e[3;36mDarkest Secret 😈: \e[0m" << this->darkest_secret << std::endl;
}
