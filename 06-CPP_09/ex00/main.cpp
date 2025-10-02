/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:02:59 by dabouab           #+#    #+#             */
/*   Updated: 2025/03/20 12:47:34 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>

void	error(std::string msg) {
	std::cout << COLOR(90) << "Error: " << msg  << COLOR(0) << std::endl;
}

int	main(int ac, char **av) {
	if (ac != 2)
		return(error("wrong number of arguments"), 1);

	BitcoinExchange 	data("data.csv", ",");
	std::fstream		input;

	input.open(av[1], std::ios_base::in);
	if (input.fail())
		return (error("no such file or directory"), 1);

	std::string			line;

	std::getline(input, line);
	while (std::getline(input, line)) {
		std::string::iterator	pos;
		std::string				date;
		std::string				value;

		pos = std::find(line.begin(), line.end(), " | "[0]);
		date = line.substr(0, std::distance(line.begin(), pos));
		value = line.substr(std::distance(line.begin(), pos) + 3, std::distance(line.begin(), line.end()));
		data.find_rate(date, value);
	}
	input.close();
}
