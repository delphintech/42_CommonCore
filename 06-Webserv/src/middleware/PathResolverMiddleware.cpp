/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PathResolverMiddleware.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:07:34 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 14:15:43 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "middleware/PathResolverMiddleware.hpp"
#include "Utils/Utils.hpp"

std::string resolveRootPath(const std::string &root, const std::string &thissystempath) {
	std::string resolvedRootPath = "";
	if (root != "" && root[0] == '.')
		resolvedRootPath = thissystempath + root.substr(1);//remove the dot
	else if (root != "" && isalnum(root[0]))
		resolvedRootPath = thissystempath + root;//add the root
	else if (root != "" && root[0] == '/')
		resolvedRootPath = root;
	else
		resolvedRootPath = thissystempath;//default root
	return resolvedRootPath;
}

std::string resolveLocationRootPath(const std::string &locationRoot,const std::string &serverRoot, const std::string &thissystempath) {
	std::string resolvedRootPath = "";
	if (locationRoot != "" && locationRoot[0] == '.')
		resolvedRootPath = serverRoot + locationRoot.substr(1);//remove the dot
	else if (locationRoot != "" && isalnum(locationRoot[0]))
		resolvedRootPath = thissystempath + locationRoot;//add the root
	else if (locationRoot != "" && locationRoot[0] == '/')
		resolvedRootPath = locationRoot;
	else
		resolvedRootPath = serverRoot;//default root
	return resolvedRootPath;
}

/**
	** 3xx Redirection **
	//permanent redirection
	301 Moved Permanently -> The requested page has been permanently moved to a new location. and the method POST transformed to GET.
	308 Permanent Redirect -> The requested page has been permanently moved to a new location. and the method should not be changed.
	//temporary redirection
	302 Found -> The requested page has been temporarily moved to a new location.
	303 See Other -> The requested page can be found under a different URI. and method POST transformed to GET.
	307 Temporary Redirect -> The requested page has been temporarily moved to a new location. and the method should not be changed.
*/
bool isRedirect(Request* req, Response* res, const DomainConfig *Dmnconfig, Location &locations) {
	if (locations.getReturn() != "")
	{
		std::string code = locations.getReturn().substr(0, 3);
		if (code == "301" || code == "302" || code == "303" || code == "307" || code == "308")
		{
			std::string newUrl = "";
			size_t pos = locations.getReturn().find("http");
			if (pos != std::string::npos)
			{
				newUrl = locations.getReturn().substr(pos);
				res->setHeader(Dmnconfig->getAddHeaders());
				std::string newUri =req->getPath().substr(locations.getUri().size());
				res->setHeader("Location", newUrl + newUri)
				.setStatusCode(Utils::String::str_to_int(code))
				.setBody("").setContentType("text/html").setContentLength(0)
				.setKeepAlive(req->getHeader("Connection") != "close");
				return true;
			}
		}
	}
	return false;
}


bool PathResolverMiddleware::handle(Request* req, Response* res, const DomainConfig *Dmnconfig, Client *client) {
	(void)client;
//	std::cout << ORANGE << "[debug] PathResolverMiddleware::handle(Request& req, Response& res) " << RESET << __FILE__ << ":" << __LINE__ << std::endl;
//	std::cout << DIM << YELLOW << "------ [debug] server_configs host port " << RESET << Dmnconfig->getHost().first << ":" <<  Dmnconfig->getListen() << std::endl;
	//0 - set System path
	Dmnconfig = &client->getDomainConfig();
	std::string thissystempath = Utils::System::getExecutableDir() + "/";
	std::string index = "";
	std::string resolvedPath = "";
	std::string resolvedRootPath = "";
	std::string cgiPath = "";
	std::string uploadDir = "";
	std::string alias = "";
	bool autoindex = false;
	//1 - set root path
	resolvedRootPath = resolveRootPath(Dmnconfig->getRoot(), thissystempath);
	resolvedPath = resolvedRootPath;
	//2 - determine the location from the request and domain config

	//defaul upload dir
	uploadDir = resolvedPath + "/uploads/";// default upload dir if is not set in the location
	
	Location locations;
	locations = Dmnconfig->getLocation(req->getPath(), req->getMethod());

	if (isRedirect(req, res, Dmnconfig, locations))
		return false;

	resolvedPath = resolveLocationRootPath(locations.getRoot(), resolvedRootPath, thissystempath);
	req->setDocumentRoot(Utils::Path::normaliseDoubleSlashPath(resolvedPath));//set the document root for the cgi
	index = locations.getIndex();
	autoindex = locations.getAutoIndex();
	//set req->isAllowedMethod
	req->setIsAllowedMethod(locations.getMethods().empty() 
		|| std::find(locations.getMethods().begin(),
				locations.getMethods().end(),
				req->getMethod()) != locations.getMethods().end());
	//juste pour la mise en page du listing des fichiers avec un bouton delete
	req->setIsAllowedMethodDelete(std::find(locations.getMethods().begin(),
				locations.getMethods().end(),
				"DELETE") != locations.getMethods().end());
	//3 - set cgi path
	std::string ext = "";
	if (req->getPath().find(".") != std::string::npos)
		ext = req->getPath().substr(req->getPath().find("."));
	if (!ext.empty())
	{
		//remove trailing slash
		size_t pos = ext.find("/");
		if (pos != std::string::npos)
			ext = ext.substr(0, pos);
		cgiPath = locations.getCgiPath(ext);
		if (cgiPath != "")
		{
			cgiPath = resolveLocationRootPath(locations.getCgiPath(ext), resolvedRootPath, thissystempath);
			cgiPath = Utils::Path::normaliseDoubleSlashPath(cgiPath);
		}
	}

	//copy the headers
	res->setHeader(Dmnconfig->getAddHeaders());
	//set upload dir
	std::string uploadDirtmp = locations.getUploadDir();
//		std::cout << DIM << PURPLE << "------ [debug] uploadDirtmp " << RESET <<  uploadDirtmp << std::endl;
	if (uploadDirtmp != "")
		uploadDir = resolveRootPath(uploadDirtmp, resolvedRootPath);
//	std::cout << DIM << PURPLE << "------ [debug] uploadDirtmp " << RESET <<  uploadDirtmp << std::endl;

	if (cgiPath != "")
	{
		req->setIsCgi(true);
		req->setCgiPath(cgiPath);
	}
	std::string locationUploadDir = Utils::Path::normaliseDoubleSlashPath(uploadDir);
	req->setUploadDir(locationUploadDir);
	//check if uploadDir exists
	if (!Utils::System::isDirectory(locationUploadDir))
		Utils::System::createDirectory(locationUploadDir);
	alias = locations.getAlias();

	//setMaxBodySize
	req->setMaxBodySize(locations.getClientMaxBodySize() != 0?
		locations.getClientMaxBodySize()
		: Dmnconfig->getClientMaxBodySize());

//	std::cout << DIM << PURPLE << "-----avant modif- [debug] resolvedPath " << RESET <<   resolvedPath << std::endl;
	std::string tmpPath = req->getPath();
	if (alias!="")
	{
		if (locations.getUri().find("~/") != std::string::npos)
		{	
			std::string tmpUri = locations.getUri().substr(2, locations.getUri().find_last_of("/") - 1);
//			std::cout << DIM << PURPLE << "---**--- [debug] 1 tmpUri " << RESET <<   tmpUri << std::endl;
			tmpPath.replace(tmpPath.find(tmpUri), tmpUri.length(), alias);
		}
		else
		//find and replace alias in the resolved path
			tmpPath.replace(tmpPath.find(locations.getUri()), locations.getUri().length(), alias);
		resolvedPath += tmpPath;
	}else
	//4 - add the request path to the resolved path
		resolvedPath += req->getPath();
	//5 - set index file
	//cas general
	if (req->getPath().find(".") == std::string::npos) //if the path does not contain a dot and index is set
	{
		//1er cas: index existe dans la location
		if (index != ""){
			resolvedPath += "/";
			resolvedPath += index;			
		}
		else if (!autoindex) {//2eme cas: autoindex is off
			//a- il existe un index dans le server
			resolvedPath += "/";
			resolvedPath += Dmnconfig->getIndex();
		}
	}
	//normalize the path
	resolvedPath = Utils::Path::normaliseDoubleSlashPath(resolvedPath);
	resolvedPath = Utils::Path::normalizePath(resolvedPath);
	req->setResolvedPath(resolvedPath);
	return true;
}