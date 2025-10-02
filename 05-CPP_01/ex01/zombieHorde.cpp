/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:13:59 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 14:08:05 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie*	zombieHorde( int N, std::string name )
{
	int		i;
	Zombie	*horde;

	horde = new Zombie[N];
	i = 0;
	while (i < N)
		horde[i++].setName(name);
	return (horde);
}