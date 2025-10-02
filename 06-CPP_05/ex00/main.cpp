/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:56:02 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/11 14:36:04 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void) {
	std::string name;
	int			grade;
	char		choice = 'o';

	std::cout << COLOR(34) << "What is the name of your Bureaucrat ?" << std::endl;
	std::cout << "> " << COLOR(0);
	std::cin >> name;
	std::cout << std::endl;
	std::cout << COLOR(34) << "What is its grade ?" << std::endl;
	std::cout << "> " << COLOR(0);
	std::cin >> grade;
	std::cout << std::endl << std::endl;

	try {
		Bureaucrat	 one(name, grade);
		Bureaucrat	two(one);

		std::cout << "Welcome to " << one <<  std::endl;
		std::cout << "And it's copy:  " << two <<  std::endl << std::endl;

		while (42)
		{
			std::cout << COLOR(34) << "Upgrade (u), downgrade (d) or exit (e) ?" << std::endl << "> " << COLOR(0);
			std::cin >> choice;
			if (choice == 'u')
			{
				std::cout << one.getName() << " just had a promotion! 😃" << std::endl;
				std::cout <<  one.upGrade() << std::endl;
			}
			if (choice == 'd')
			{
				std::cout << one.getName() << " just had a demotion! 😞" << std::endl;
				std::cout <<  one.downGrade() << std::endl;
			}
			if (choice == 'e')
				break ;
			std::cin.clear();
			std::cin.ignore();
		}
	}
	catch (std::exception &e) {
		std::cout << "🚨 Error: " << e.what() << std::endl;
	}

}