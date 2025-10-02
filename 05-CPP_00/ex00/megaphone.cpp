/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:18:39 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/21 12:36:18 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main (int ac, char **av)
{
	int	i;
	int	j;
	
	if (ac < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	else
	{
		i = 1;
		while (i < ac)
		{
			j = 0;
			while (av[i][j])
				std::cout << (char)std::toupper(av[i][j++]);
			i++;
		}
		std::cout << "\n";
	}
}
