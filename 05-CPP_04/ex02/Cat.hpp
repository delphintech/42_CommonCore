/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 15:05:15 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : virtual public Animal {
	private:
		Brain	*brain;
		
	public:
		Cat();
		Cat(const Cat& arg);
		Cat&	operator=(const Cat& arg);
		~Cat();

		Brain	*getBrain() const;
		void	makeSound() const;
};

#endif
