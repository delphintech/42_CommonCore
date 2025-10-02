/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:40:27 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/20 15:49:46 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {};
ScalarConverter::ScalarConverter(const ScalarConverter& scalar) { (void)scalar; };
ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& scalar) { (void)scalar; return (*this); }
ScalarConverter::~ScalarConverter() {}

bool	ScalarConverter::is_round(double d) {
	int		n;
	double	rest;	

	n = static_cast<int>(d);
	rest = std::abs(d - n);
	if (rest > 0)
		return (false);
	return (true);
}

void	ScalarConverter::print_char(char c) {
	std::cout << "char: ";
	if (std::isprint(c) == 0)
		std::cout << "non displayable" << std::endl;
	else
		std::cout << c << std::endl;
}

void	ScalarConverter::print_int(int i) {
	std::cout << "int: " << i << std::endl;
}

void	ScalarConverter::print_float(float f) {
	std::cout << "float: " << f << (is_round(f) ? ".0" : "") << "f" << std::endl;
}

void	ScalarConverter::print_double(double d) {
	std::cout << "double: " << d << (is_round(d) ? ".0" : "") << std::endl;
}

void	ScalarConverter::print_error() {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: nanf" << std::endl;
	std::cout << "double: nan" << std::endl;
}

void	ScalarConverter::toChar(std::string str) {
	char	c = static_cast<char>(str[0]);
	
	print_char(c);
	print_int(static_cast<int>(c));
	print_float(static_cast<float>(c));
	print_double(static_cast<double>(c));
}

void		ScalarConverter::toInt(std::string str) {
	int	i = std::atof(str.c_str());

	if (i > std::numeric_limits<char>::max() || i < std::numeric_limits<char>::min())
		std::cout << "char: impossible" << std::endl;
	else
		print_char(static_cast<char>(i));
	if (i > std::numeric_limits<int>::max()
		|| i < std::numeric_limits<int>::min())
		std::cout << "int: impossible" << std::endl;
	else
		print_int(i);
	print_float(static_cast<float>(i));
	print_double(static_cast<double>(i));
}

void	ScalarConverter::toFloat(std::string str) {
	float	f = std::atof(str.c_str());
	
	if (f > std::numeric_limits<char>::max()
		|| f < std::numeric_limits<char>::min())
		std::cout << "char: impossible" << std::endl;
	else
		print_char(static_cast<char>(f));
		
	if (f > std::numeric_limits<int>::max()
		|| f < std::numeric_limits<int>::min())
		std::cout << "int: impossible" << std::endl;
	else
		print_int(static_cast<int>(f));
	print_float(f);
	print_double(static_cast<double>(f));
}

void	ScalarConverter::toDouble(std::string str) {
	double	d = std::atof(str.c_str());
	
	if (d > std::numeric_limits<char>::max()
		|| d < std::numeric_limits<char>::min())
		std::cout << "char: impossible" << std::endl;
	else
		print_char(static_cast<char>(d));
		
	if (d > std::numeric_limits<int>::max()
		|| d < std::numeric_limits<int>::min() || std::isinf(d))
		std::cout << "int: impossible" << std::endl;
	else
		print_int(static_cast<int>(d));

	print_float(static_cast<float>(d));
	print_double(d);
}

void ScalarConverter::convert(std::string str) {
	bool	test = true;
	
	for (size_t i = 0; i < str.length(); i++) {
		if (std::isdigit(str[i]) == 0 && 
			(str[i] != '.' 
				&& !(str[i] == 'f' && i == str.length() - 1))
				&& !(str[i] == '-' && i == 0))
			test = false;
	}
	if (str.length() < 2 && std::isdigit(str[0]) == 0)
		toChar(str);
	else if (test && str.find(".") == std::string::npos)
		toInt(str);
	else if (test && str.find("f") != std::string::npos)
		toFloat(str);
	else if (test) 
		toDouble(str);
	else
		print_error();
}
