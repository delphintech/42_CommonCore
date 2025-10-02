/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiddlewareChain.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:04:25 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:39:36 by nbrigui          ###   ########.fr       */
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
#include "class/DomainConfig.hpp"

class MiddlewareChain {
	private:
		std::vector<AMiddleware*> middlewares;
		size_t current;
		const DomainConfig *_dmnconfig;
		Client *_client;

	public:
		MiddlewareChain(const DomainConfig *Dmnconfig, Client *client);
		~MiddlewareChain();

		void addMiddleware(AMiddleware* middleware);
		void execute(Request* req, Response* res);
		DomainConfig *getDomainConfig() const;
};