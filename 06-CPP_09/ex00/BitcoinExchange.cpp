/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:57:30 by dabouab           #+#    #+#             */
/*   Updated: 2025/03/20 12:54:06 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/********** Canonical form **********/
BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& model) {
	std::multimap<time_t, float>::const_iterator	it;

	for (it = model._data.begin(); it != model._data.end(); it++) {
		this->_data.insert(std::pair<time_t, float>(it->first, it->second));
	}
}

BitcoinExchange::BitcoinExchange(const char* file, std::string delimiter) {
	std::fstream	input;
	std::string		line;

	input.open(file, std::ios_base::in);
	if (input.fail())
		error("no such file or directory");

	std::getline(input, line);
	while (std::getline(input, line)) {
		std::string::iterator	pos;
		Date					d;
		std::string				date;
		std::string				value;

		memset(&d, 0, sizeof(d));
		pos = std::find(line.begin(), line.end(), delimiter[0]);
		date = line.substr(0, std::distance(line.begin(), pos));
		value = line.substr(std::distance(line.begin(), pos) + delimiter.size(), std::distance(line.begin(), line.end()));
		strptime(date.c_str(), "%Y-%m-%d", &d);
		this->_data.insert(std::pair<time_t, float>(std::mktime(&d), std::atof(value.c_str())));
	}
	input.close();
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& model) {
	std::map<time_t, float>::const_iterator	it;

	if (this == &model)
		return (*this);

	this->_data.clear();
	for (it = model._data.begin(); it != model._data.end(); it++) {
		this->_data.insert(std::pair<time_t, float>(it->first, it->second));
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {
	_data.clear();
}

void	BitcoinExchange::display() {
	std::string								date;
	std::map<time_t, float>::const_iterator	it;

	for (it = this->_data.begin(); it != this->_data.end(); it++) {
		std::cout << "Date: " << std::ctime(const_cast<time_t*>(&it->first)) << ", Value: " << it->second << std::endl;
	}
}

void	BitcoinExchange::find_rate(std::string date, std::string value) {
	float	val = std::atof(value.c_str());
	Date	d;

	memset(&d, 0, sizeof(d));
	if (!strptime(date.c_str(), "%Y-%m-%d", &d) || value.empty())
		return (error("bad input => " + date));
	if (val == 0 && !(!value.compare("0") || !value.compare("0.0") || !value.compare("0.0f")))
		return (error("not a number"));
	if (val < 0)
		return (error("not a positive number"));
	if (val > 1000)
		return (error("too large number"));

	std::multimap<time_t, float>::reverse_iterator	rit;

	rit = this->_data.rbegin();
	while (rit != this->_data.rend() && std::difftime(std::mktime(&d), rit->first) < 0) {
		if (std::difftime(std::mktime(&d), rit->first) == 0)
			break ;
		rit++;
	}
	if (rit == this->_data.rend())
		return (error("no value found"));
	std::cout << date << " => " << value << " = " << rit->second * val << std::endl;
}
