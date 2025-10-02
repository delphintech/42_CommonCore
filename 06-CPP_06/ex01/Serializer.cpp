/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:48:13 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/20 17:21:57 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

/********** Canonical **********/
Serializer::Serializer() {}
Serializer::Serializer(const Serializer& model) { (void)model; }
Serializer& Serializer::operator=(const Serializer& model) { (void)model; return (*this); }
Serializer::~Serializer() {}

/********** Methods **********/
uintptr_t	Serializer::serialize(Data* ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*		Serializer::deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data*>(raw));
}