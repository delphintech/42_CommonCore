/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Derived.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:28:53 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/21 13:34:03 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

A::A() {}
A::~A() {}
A& A::operator=(A& obj) { (void)obj; return (*this); }

B::B() {}
B::~B() {}
B& B::operator=(B& obj) { (void)obj; return (*this); }

C::C() {}
C::~C() {}
C& C::operator=(C& obj) { (void)obj; return (*this); }
