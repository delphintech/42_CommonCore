/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:40:17 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 13:05:33 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BASE_CPP
#define BASE_CPP

#include <iostream>
#include <cstdlib>
#include <ctime>

#define COLOR(nb) "\e["#nb"m"

class Base
{
public:
	virtual ~Base();

	static Base * generate(void);
	static void identify(Base* p);
	static void identify(Base& p);
};


#endif
