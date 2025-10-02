/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:25:47 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 12:24:53 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string.h>
#include "utils.hpp"

#ifndef CONTACT_HPP
# define CONTACT_HPP

class Contact {
private:
	std::string	name;
	std::string	last_name;
	std::string	nickname;
	std::string	phone;
	std::string	darkest_secret;

	bool	CheckNum();
	void	Display();

public:
	Contact(void);
	~Contact(void);

	void				Add();
	void				SearchDisplay(int index);
	void				FullDisplay();
	std::string	getPhone();
};

#endif
