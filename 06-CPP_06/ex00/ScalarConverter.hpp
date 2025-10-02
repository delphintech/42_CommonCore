/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:40:13 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/20 15:49:30 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <limits>
#include <cmath>

#define COLOR(nb) "\e["#nb"m"

class ScalarConverter
{
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& scalar);
	ScalarConverter&	operator=(const ScalarConverter& scalar);

	static bool		is_round(double d);
	static void		print_char(char c);
	static void		print_int(int i);
	static void		print_float(float f);
	static void		print_double(double d);
	static void		print_error();
	
	static void		toChar(std::string str);
	static void		toInt(std::string str);
	static void		toFloat(std::string str);
	static void		toDouble(std::string str);
	
public:
	~ScalarConverter();

	static void convert(std::string str);
};

#endif
