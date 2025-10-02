/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:51:39 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:34:32 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() {
	std::cout << COLOR(90) << "🧠 Default" << COLOR(0) << std::endl;
}

Brain::Brain(const Brain& arg) {
	std::cout << COLOR(90) << "🧠 Copy" << COLOR(0) << std::endl;
	int	i = 0;
	
	while (i < 100)
	{
		if (!arg._ideas[i].empty())
			this->_ideas[i] = arg._ideas[i];
		i++;
	}
}

Brain&	Brain::operator=(const Brain& arg) {
	std::cout << COLOR(90) << "🧠 Assignment operator" << COLOR(0) << std::endl;
	int	i = 0;

	while (i < 100)
	{
		if (!arg._ideas[i].empty())
			this->_ideas[i] = arg._ideas[i];
		i++;
	}
	return (*this);
}

Brain::~Brain() {
	std::cout << COLOR(90) << "🧠  Destructor" << COLOR(0) << std::endl;
}

void	Brain::add_idea(std::string arg) {
	int	i = 0;
	
	while (i < 100)
	{
		if (this->_ideas[i].empty())
		{
			this->_ideas[i] = arg;
			break ;
		}
		i++;
	}
}
void	Brain::show_ideas() {
	int	i = 0;
	
	std::cout << "Ideas: ";
	while (i < 100)
	{
		if (!this->_ideas[i].empty())
			std::cout << this->_ideas[i] << " ";
		i++;
	}
	std::cout << std::endl;
}