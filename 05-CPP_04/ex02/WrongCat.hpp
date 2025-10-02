/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:28:39 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 10:08:11 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : virtual public WrongAnimal {
	private:

	public:
		WrongCat();
		WrongCat(const WrongCat& arg);
		WrongCat&	operator=(const WrongCat& arg);
		~WrongCat();
};

#endif
