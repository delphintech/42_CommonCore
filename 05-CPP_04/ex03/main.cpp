/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:54:22 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/19 11:11:09 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

void	blue_print(std::string str) {
	std::cout << "\e[34;1m" << str << "\e[0m" << std::endl;
}

int main()
{
	blue_print("Creating new materia and source ...");
	IMateriaSource* src = new MateriaSource();
	Ice		ice;
	Cure	cure;
	
	blue_print("Source learns materia ...");
	src->learnMateria(&ice);
	src->learnMateria(&cure);
	
	blue_print("Creating Lea character and giving her 2 new materia ...");
	Character* lea = new Character("Lea");
	
	AMateria* tmp;
	tmp = src->createMateria("ice");
	lea->equip(tmp);
	tmp = src->createMateria("cure");
	lea->equip(tmp);

	blue_print("Creating Bob character and giving him 1 materia, dropping it and taking another one ...");
	Character* bob = new Character("bob");
	tmp = src->createMateria("ice");
	bob->equip(tmp);
	bob->unequip(0);
	tmp = src->createMateria("cure");
	bob->equip(tmp);

	blue_print("Character deep copy ...");
	Character	*copy = new Character(*lea);
	Character	*another = new Character("copy");
	*another = *bob;
	std::cout << bob->getName() << ": " << bob << ", " << another->getName() << " (copy): " << another << std::endl;
	std::cout << lea->getName() << ": " << lea << ", " << copy->getName() << " (copy): " << copy << std::endl;

	blue_print("Using the materia ...");
	lea->use(0, *bob);
	lea->use(1, *bob);
	copy->use(1, *bob);
	bob->use(0, *bob);
	another->use(0, *bob);
	
	blue_print("Cleaning everything ...");
	delete	bob;
	delete	lea;
	delete	copy;
	delete	another;
	delete	src;
	for (int i = 0; i < MAX_DROPS; i++)
		delete AMateria::drops[i];
	
	return (0);
}