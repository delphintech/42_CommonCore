/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentResponseFactoryMiddleWare.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:31:11 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 15:04:06 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "middleware/ContentResponseFactoryMiddleWare.hpp"
#include "Utils/Utils.hpp"
#include "responseFactory/StaticFileResponseHandler.hpp"
#include "responseFactory/DirectoryListerResponseHandler.hpp"
#include "responseFactory/CgiResponseHandler.hpp"

/**
 * @brief handle the request and create the response
 */
bool ContentResponseFactoryMiddleWare::handle(Request* req, Response* res, const DomainConfig *Dmnconfig, Client *client) {
	(void)Dmnconfig;
	 _dmnconfig = &client->getDomainConfig();
	(void)client;
	if (resolvePath(req, res)) {
		return false;
	}
	return true;
}

/**
 * @brief create the response handler based on the path type
 * @param pathType the type of the path
 * @param req the request
 * @return the response handler from responseFactory/
 *  or nullptr if the path type is not found * 
 */
IResponseHandler *ContentResponseFactoryMiddleWare::createResponseHandler(PathType pathType,Request *req) {
	switch (pathType) {
		case P_FILE:
			return new StaticFileResponseHandler(req->getPath(),req->getResolvedPath(), req);//	StaticFileResponseHandler directoryListerResponse(req->getPath(),"/home/nbrigui/42cursus/42-webserv/var/testphp/upload_store/Capture d’écran du 2025-01-08 06-58-29.png", req);
		case P_DIRECTORY:
			return new DirectoryListerResponseHandler(req->getPath(),req->getResolvedPath(), req);//DirectoryListerResponseHandler directoryListerResponse(req->getPath(),"/home/nbrigui/42cursus/42-webserv/", req);
		case P_CGI :
			return new CgiResponseHandler(req->getCgiPath(),req->getResolvedPath(), req, _dmnconfig);//cgiResponse("/usr/bin/php-cgi","/home/nbrigui/42cursus/42-webserv/var/testphp/postMultipart.php", req);
		case P_NOT_FOUND:
		default:
			return nullptr;
	}
	return nullptr;
}

bool ContentResponseFactoryMiddleWare::resolvePath(Request *req, Response *res) {
	std::string path = req->getResolvedPath();
	PathType pathType;
	if (req->isCgi() ) {
		pathType = P_CGI;
	} else {
		pathType = Utils::System::resolvePathType(path);
	}
	
	switch (pathType) {
		case P_CGI:
			if (!Utils::System::hasExecutePermission(req->getCgiPath())) {
				
				std::cerr << "req->getCgiPath : " << req->getCgiPath() << std::endl;
				std::cerr << "path " << path << std::endl;
				std::cerr << "hasExecutePermission " << (Utils::System::hasExecutePermission(req->getCgiPath()) ? "true" : "false")  << std::endl;
				std::cerr << "hasReadPermission " << (Utils::System::hasReadPermission(path) ? "true" : "false")  << std::endl;
				res->setError(403);
				return false;
			}
			//
			break;
		case P_FILE:
			if (!Utils::System::hasReadPermission(path)) {
				res->setError(403);
				return false;
			}
			break;
		case P_DIRECTORY:
			break;

		case P_NOT_FOUND:
		default:
			res->setError(404);
			return false;
	}

	IResponseHandler *responseHandler = createResponseHandler(pathType,req);
	if (responseHandler == nullptr) {
		res->setError(500);
		return false;
	}
	responseHandler->getBody();
	responseHandler->generateHeaders(res);
	delete responseHandler;
	return true;
}
