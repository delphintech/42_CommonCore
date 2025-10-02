/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:57:39 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/27 17:18:59 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#define COLOR(nb) "\e["#nb"m"

#include <iostream>
#include <map>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <sstream>

typedef struct tm	Date;

void	error(std::string msg);

class BitcoinExchange
{
private:
	std::multimap<time_t, float>	_data;

public:
/********** Canonical form **********/
	BitcoinExchange();
	BitcoinExchange(const char* file, std::string delimiter);
	BitcoinExchange(const BitcoinExchange& model);
	BitcoinExchange& operator=(const BitcoinExchange& model);
	~BitcoinExchange();

/********** Function **********/
	void	display();
	void	find_rate(std::string date, std::string value);
};

#endif
