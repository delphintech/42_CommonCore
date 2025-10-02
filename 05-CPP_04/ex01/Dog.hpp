/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:47:09 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 15:04:19 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : virtual public Animal {
	private:
		Brain	*brain;

	public:
		Dog();
		Dog(const Dog& arg);
		Dog&	operator=(const Dog& arg);
		~Dog();

		Brain	*getBrain() const;
		void	makeSound() const;
};

#endif
