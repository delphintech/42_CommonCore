/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentResponseFactoryMiddleWare.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:46:06 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:48:12 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef nullptr
#define nullptr NULL
#endif

#include <map>
#include <vector>

#include "middleware/AMiddleware.hpp"
#include "Utils/Utils.hpp"
#include "responseFactory/IResponseHandler.hpp"

class ContentResponseFactoryMiddleWare : public AMiddleware {
	private:
		const DomainConfig *_dmnconfig;
		bool resolvePath(Request *req, Response *res);
	public:
		IResponseHandler *createResponseHandler(PathType pathType,Request *req);
		bool handle(Request* req, Response* res, const DomainConfig *Dmnconfig = NULL, Client *client = NULL);
};