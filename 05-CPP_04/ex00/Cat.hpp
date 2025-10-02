/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:00:18 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include "Animal.hpp"

class Cat : virtual public Animal {
	public:
		Cat();
		Cat(const Cat& arg);
		Cat&	operator=(const Cat& arg);
		~Cat();

		void	makeSound() const;
};

#endif
