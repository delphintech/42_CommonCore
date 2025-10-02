/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiiddlewareChain.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:07:11 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 14:12:30 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "middleware/MiddlewareChain.hpp"
#include "class/Client.hpp"

MiddlewareChain::MiddlewareChain(const DomainConfig *Dmnconfig, Client *client) : current(0), _dmnconfig(Dmnconfig), _client(client){}

MiddlewareChain::~MiddlewareChain() {
	for (std::vector<AMiddleware*>::iterator it = middlewares.begin(); it != middlewares.end(); ++it) {
		delete *it;
	}
}

void MiddlewareChain::addMiddleware(AMiddleware* middleware) {
	middlewares.push_back(middleware);
}

void MiddlewareChain::execute(Request *req, Response *res) {
	if (current < middlewares.size()) {
		AMiddleware* middleware = middlewares[current++];
		if (middleware->handle(req, res, _dmnconfig, _client)) {
			execute(req, res);
		}
	}
}