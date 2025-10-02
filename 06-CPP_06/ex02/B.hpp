/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:34:16 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 13:31:53 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_HPP
#define B_HPP

#include <iostream>
#include "Base.hpp"

class B : public Base
{
public:
	B();
	~B();
	B& operator=(B& obj);
};

#endif
