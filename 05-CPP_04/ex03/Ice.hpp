/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:54:20 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 17:14:28 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

#include <iostream>
#include "AMateria.hpp"

class Ice : virtual public AMateria {
public:
	Ice();
	Ice(const Ice& arg);
	Ice& operator=(const Ice& arg);
	~Ice();
	
	Ice*	clone() const;
	void	use(ICharacter& target);
};

#endif