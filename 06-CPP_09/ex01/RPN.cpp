/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:31:16 by dabouab           #+#    #+#             */
/*   Updated: 2025/03/20 13:02:37 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/********** Canonical form **********/
RPN::RPN() {}

RPN::RPN(char* str) {
	_str = str;
}

RPN::RPN(RPN& model) {
	_stack = model._stack;
}

RPN& RPN::operator=(RPN& model) {
	if (this == &model)
		return (*this);
	while (_stack.empty()) {  _stack.pop(); }
	this->_stack = model._stack;
	return (*this);
}

RPN::~RPN() { while (_stack.empty()) {  _stack.pop(); } }

/********** Functions **********/
const std::stack<int>&	RPN::getStack() const { return (this->_stack); }

int	calcul(int first, int second, char operand) {
	switch (operand)
	{
	case '+':
		return (second + first);
		break;
	case '-':
		return (second - first);
		break;
	case '*':
		return (second * first);
		break;
	case '/':
		return (second / first);
		break;
	default:
		return (-1);
		break;
	}
	}

int	RPN::total() {
	std::string::iterator	it = this->_str.begin();
	std::string				operands = "+-*/";
	int	first;
	int	second;
	
	while (it != _str.end()) {
		if (std::isdigit(*it))
			this->_stack.push(*it - '0');
		else if (operands.find(*it) != std::string::npos && this->_stack.size() >= 2)
		{
			first = this->_stack.top();
			this->_stack.pop();
			second = this->_stack.top();
			this->_stack.pop();
			this->_stack.push(calcul(first, second, *it));
		}
		else if (*it == ' ') {}
		else
			return (-1);
		it++;
	}
	if (this->_stack.size() != 1)
		return (-1);
	return (this->_stack.top());
}