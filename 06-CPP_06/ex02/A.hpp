/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:05:20 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 13:31:40 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_HPP
#define A_HPP

#include <iostream>
#include "Base.hpp"

class A : public Base
{
public:
	A();
	~A();
	A& operator=(A& obj);
};

#endif
