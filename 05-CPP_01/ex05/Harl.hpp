/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:05:49 by dabouab           #+#    #+#             */
/*   Updated: 2024/12/09 14:23:32 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>

class Harl {
private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);
	
public:
	Harl(void);
	~Harl(void);
	void	complain(std::string level);
};

#endif