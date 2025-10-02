/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:59:59 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 15:04:52 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal {
	protected:
		std::string	type;
		Animal();
		Animal(std::string type);
		Animal(const Animal& arg);
		Animal&	operator=(const Animal& arg);

	public:
		std::string		getType() const;
		virtual void	makeSound() const = 0;
		virtual ~Animal();
};

#define COLOR(nb) "\e["#nb"m"

#endif
