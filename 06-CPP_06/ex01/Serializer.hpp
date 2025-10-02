/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:48:24 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/20 16:55:31 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#define COLOR(nb) "\e["#nb"m"

#include <iostream>
#include <stdint.h>
#include "Data.hpp"

class Serializer
{
private:
	Serializer();
	Serializer(const Serializer& model);
	Serializer& operator=(const Serializer& model);

public:
	~Serializer();

/********** Methods **********/
	static uintptr_t	serialize(Data* ptr);
	static Data*		deserialize(uintptr_t raw);
};

#endif
