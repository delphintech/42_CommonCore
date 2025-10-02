/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:47:09 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:00:23 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include <iostream>
#include "Animal.hpp"

class Dog : virtual public Animal {
	public:
		Dog();
		Dog(const Dog& arg);
		Dog&	operator=(const Dog& arg);
		~Dog();

		void	makeSound() const;
};

#endif
