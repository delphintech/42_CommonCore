/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:14:58 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 17:15:22 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

#include <iostream>
#include "AMateria.hpp"

class Cure : virtual public AMateria {
public:
	Cure();
	Cure(const Cure& arg);
	Cure& operator=(const Cure& arg);
	~Cure();
	
	Cure*	clone() const;
	void	use(ICharacter& target);
};

#endif