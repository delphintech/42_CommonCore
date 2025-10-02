/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequestHandlerMiddleware.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:13:28 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:49:02 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef nullptr
#define nullptr NULL
#endif

#include <map>
#include <vector>
#include <algorithm>
#include "middleware/AMiddleware.hpp"

class ParseRequestHandlerMiddleware : public AMiddleware {
	public:
		bool handle(Request* req, Response* res, const DomainConfig *Dmnconfig = NULL, Client *client = NULL);
};
