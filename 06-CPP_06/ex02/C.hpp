/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:04 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 13:32:13 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_HPP
#define C_HPP

#include <iostream>
#include "Base.hpp"

class C : public Base
{
public:
	C();
	~C();
	C& operator=(C& obj);
};

#endif
