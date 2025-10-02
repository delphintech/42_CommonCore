/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:55 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:26:31 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed {
private:
	int					_raw;
	static const int	_fract;

public:
	Fixed();
	Fixed(Fixed& fixed);
	Fixed& operator=(const Fixed& fixed);
	~Fixed();
	
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
};

#endif
