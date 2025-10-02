/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:40:14 by dabouab           #+#    #+#             */
/*   Updated: 2024/11/27 12:25:06 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <limits>
#include "utils.hpp"
#include "Contact.hpp"

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

class Phonebook {
private:
	Contact list[8];

	int	Display();

public:
	Phonebook(void);
	~Phonebook(void);

	void	Search();
	void	Add();
};

#endif
