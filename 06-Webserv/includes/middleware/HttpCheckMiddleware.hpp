/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCheckMiddleware.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:28:52 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:49:52 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "middleware/AMiddleware.hpp"
#include "Utils/Utils.hpp"

class HttpCheckMiddleware : public AMiddleware {
	public:
		bool handle(Request* req, Response* res, const DomainConfig *Dmnconfig = NULL, Client *client = NULL);
};