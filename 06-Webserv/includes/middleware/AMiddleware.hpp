/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMiddleware.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:05:09 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:49:40 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef nullptr
#define nullptr NULL
#endif

#include <map>
#include "request/Request.hpp"
#include "response/Response.hpp"
#include "class/DomainConfig.hpp"
#include "class/Client.hpp"

class AMiddleware {
	public:
		virtual ~AMiddleware() {}
		virtual bool handle(Request *req, Response *res, const DomainConfig *Dmnconfig = NULL, Client *client = NULL) = 0;
};