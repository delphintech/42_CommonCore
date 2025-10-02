/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   String.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/07 14:08:00 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/Utils.hpp"
#include "webserv.h"

std::string Utils::String::intToString(int n)
{
	std::string str;
	std::string str2;
	int i = 0;
	if (n == 0)
		return "0";
	if (n < 0)
	{
		n = -n;
		str2 = "-";
	}
	while (n > 0)
	{
		str += n % 10 + '0';
		n /= 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		str2 += str[i];
		i--;
	}
	return str2;
}

void	Utils::String::trim(std::string &str, char *set) {
	size_t first;
	size_t last;
	
	for (size_t i = 0; i < strlen(set); i++) {
		first = str.find_first_not_of(set[i]);
		last = str.find_last_not_of(set[i]) + 1;
		if (first == std::string::npos || last == std::string::npos)
			continue ;
		str = str.substr(first, last - first);
	}
}

std::string	Utils::String::get_between(std::string &str, std::string prev, std::string next) {
	std::string	word;
	
	size_t first = str.find(prev) + prev.size();
	size_t last = str.find(next);
	if (first == std::string::npos || last == std::string::npos)
		return (str);
	word = str.substr(first, last - first);
	if (word.empty())
		return ("");
	Utils::String::trim(word, (char *)"\t\n\r\v\f ");
	return (word);
}

std::vector<std::string>	Utils::String::str_to_vect(std::string str, char delimiter)
{
	std::vector<std::string>	vector;
	size_t					start;
	size_t					end;

	start = 0;
	end = 1;
	while (end < str.size())
	{
		end = str.find(delimiter, start);
		if (end == std::string::npos)
			end = str.size();
		vector.push_back(str.substr(start, end - start));
		start = end;
		while (start < str.size() && str.at(start) == delimiter)
			start++;
	}
	return (vector);
}

int	Utils::String::str_to_int(std::string str) {
	std::stringstream	stream;
	int					n = 0;

	stream << str;
	stream >> n;
	return (n);
}

std::string	Utils::String::toUpper(std::string str) {
	std::string	upper;

	for (size_t i = 0; i < str.size(); i++) {
		upper += toupper(str[i]);
	}
	return (upper);
}

std::string Utils::String::urlDecode(const std::string &encoded) {
	std::ostringstream decoded;
	for (size_t i = 0; i < encoded.size(); ++i) {
		if (encoded[i] == '%' && i + 2 < encoded.size()) {
			std::istringstream hex(encoded.substr(i + 1, 2));
			int value;
			if (hex >> std::hex >> value) {
				decoded << static_cast<char>(value);
				i += 2;
			} else {
				decoded << '%';
			}
		} else if (encoded[i] == '+') {
			decoded << ' ';
		} else {
			decoded << encoded[i];
		}
	}
	return decoded.str();
}