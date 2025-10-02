/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpIsAllowedMethodMiddleware.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:07:34 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:51:09 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "middleware/HttpIsAllowedMethodMiddleware.hpp"
#include "Utils/Utils.hpp"
#include "parseFormData/MultipartFormDataParser.hpp"
#include "parseFormData/OtherParser.hpp"

bool HttpIsAllowedMethodMiddleware::handle(Request* req, Response* res, const DomainConfig *Dmnconfig, Client *client) {
	(void)Dmnconfig;
	(void)client;
	if (req->getMethod() == "OPTIONS") {
		res->setHeader("Allow", "GET, POST, PUT, DELETE, OPTIONS");
		res->setError(200);
		return false;
	}
	//is allowed method
	if (!req->isAllowedMethod()) {
		res->setError(405);
		return false;
	}

	//check the body size
	if (req->getMaxBodySize() != 0 && req->getBodySize() > req->getMaxBodySize()) {
		res->setError(413);
		return false;
	}
	
	/**
	 * @TODO implement the allowed methods
	 * and POST Response
	 */
	if ((req->getMethod() == "POST" || req->getMethod() == "PUT") && !req->isCgi()) {
		std::string contentType = req->getHeader("Content-Type");

		if (contentType.find("multipart/form-data") != std::string::npos) {
			return MultipartFormDataParser::handleMultipartFormData( *req, *res);
		}
		else {
			return	OtherParser::handleOtherParserFormData(*req, *res);
		}
	}

	if (req->getMethod() == "DELETE") {
		if (Utils::System::isDirectory(req->getResolvedPath()) || !Utils::System::isFile(req->getResolvedPath()))
		{
			res->setError(404);//not found
			return false;
		}
		if (remove(req->getResolvedPath().c_str()) != 0 )
		{
			res->setError(500);//internal server error
			return false;
		}
		res->setError(204);//no content
		return false;
	}	
	return true;
}