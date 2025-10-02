/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:25:42 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:07:42 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONG_ANIMAL_HPP
# define WRONG_ANIMAL_HPP

#include <iostream>

class WrongAnimal {
	protected:
		std::string	type;

	public:
		WrongAnimal();
		WrongAnimal(std::string type);
		WrongAnimal(const WrongAnimal& arg);
		WrongAnimal&	operator=(const WrongAnimal& arg);
		~WrongAnimal();

		std::string		getType() const;
		void	makeSound() const;
};

#define COLOR(nb) "\e["#nb"m"

#endif
