/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:50:43 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:33:24 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>

class Brain {
	private:
		std::string	_ideas[100];

	public:
		Brain();
		Brain(std::string type);
		Brain(const Brain& arg);
		Brain&	operator=(const Brain& arg);
		~Brain();

		void	add_idea(std::string arg);
		void	show_ideas();
};

#define COLOR(nb) "\e["#nb"m"

#endif