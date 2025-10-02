/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:31:28 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/28 17:53:55 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
private:
	std::stack<int>	_stack;
	std::string		_str;
	
public:
/********** Canonical form **********/
	RPN();
	RPN(char* str);
	RPN(RPN& model);
	RPN& operator=(RPN& model);
	~RPN();\

/********** Functions **********/
const std::stack<int>&	getStack() const;
int						total();
};

#endif
