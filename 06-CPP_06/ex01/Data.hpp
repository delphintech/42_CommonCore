/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:55:07 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/20 16:40:29 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>

class Data
{
private:
	std::string	_str;
	int			_i;
	
public:
/********** Canonical form **********/
	Data();
	Data(int i, std::string str);
	Data(const Data& obj);
	Data& operator=(const Data& obj);
	~Data();

/********** Getters **********/
	std::string	getStr() const;
	int			getI() const;

	void		display() const;
};

#endif
