/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:53:27 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/08 10:47:16 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>//std::stringstream

class AHTTPRequest 
{
	protected:
		std::string _nullString; //empty string
		std::string _protocol; //HTTP/1.1 //old	std::string _version;
		std::string _method; //GET
   		std::string _uri;// URI brute: /api/user?id=42&name=nbrigui
   		std::string _queryString;// query string: id=42&name=nbrigui
		std::string _path;	// path: /api/user
		std::string _host;//en trop?
		std::string _port;//en trop?
		std::map<std::string, std::string> _headers; // headers de la requête ex: Accept: text/html > _headers["Accept"] = "text/html"
		//size_t _header_size; //Taille de l'en-tête de la requête
		//std::string _body;
		std::map<std::string, std::string> _queryParams; //Paramètres de l'URL : pour les requêtes GET ou les parties après le ? dans l'URI.
														//ex: /api/user?id=42&name=nbrigui > _queryParams["id"] = "42" et _queryParams["name"] = "nbrigui"
		std::map<std::string, std::string> _bodyParams; //Paramètres du corps : pour les requêtes POST ou PUT contenant des données.
														//ex: id=42&name=nbrigui > _bodyParams["id"] = "42" et _bodyParams["name"] = "nbrigui"
		std::string _requestTempFilePath;
		size_t _requestTempFilesize;
		std::string _headerRaw;
		std::string _requestRaw;

		std::string _bodyRaw; //données brutes de la requête, telles qu'envoyées par le client.
								//ex: { "id": 42, "name": "nbrigui" } > _bodyRaw = "{ \"id\": 42, \"name\": \"nbrigui\" }"
		std::map<std::string, std::string> _parsedBody;//Les données parsées, si applicables (JSON, form-data, ...)
													//ex: { "id": 42, "name": "nbrigui" } > parsedBody["id"] = "42" et parsedBody["name"] = "nbrigui"
		std::map<std::string, std::string> _cookies;//Les cookies envoyés par le client.
													//ex: session=42; user=nbrigui > cookies["session"] = "42" et cookies["user"] = "nbrigui"
	    std::string _sessionId;//non used
    	std::string _clientIp;//non used
		std::string _resolvedPath;
		std::string _uploadDir;
		size_t _header_size;
		size_t _body_size;
		int _clientFd;

		bool _isCgi;
		std::string _cgiPath;
		
		bool _isAllowedMethod;
		bool _isAllowedMethodDelete;
		size_t _maxBody_size;
		std::string _systemTmpDir;
		std::string _documentRoot;

	public:
		AHTTPRequest();
		virtual ~AHTTPRequest();
		AHTTPRequest(const AHTTPRequest &other);
		AHTTPRequest& operator=(const AHTTPRequest& other);
		AHTTPRequest* operator=(AHTTPRequest* other);

		const std::string &getMethod() const;
		const std::string &getUri() const;
		const std::string &getPath() const;
		const std::string &getProtocol() const;
		const std::string &getHost() const;
		const std::string &getPort() const;
		const std::string &getHeader(const std::string& name) const;
		std::map<std::string, std::string> getHeaders() const;
		std::string getBodyRaw() const;
		std::map<std::string, std::string> getQueryParams() const;
		AHTTPRequest& setQueryString(const std::string &queryString);
		const std::string &getQueryString() const;
		std::map<std::string, std::string> getBodyParams() const;
		std::map<std::string, std::string> getParsedBody() const;
		std::map<std::string, std::string> getCookies() const;
		const std::string &getResolvedPath() const;
		const std::string &getSessionId() const;
		const std::string &getClientIp() const;

		AHTTPRequest& setMethod(const std::string &method);
		AHTTPRequest& setIsAllowedMethod(bool isAllowedMethod);
		bool isAllowedMethod() const;
		AHTTPRequest& setIsAllowedMethodDelete(bool isAllowedMethodDelete);
		bool isAllowedMethodDelete() const;
		AHTTPRequest& setUri(const std::string &uri);
		AHTTPRequest& setPath(const std::string &path);
		AHTTPRequest& setProtocol(const std::string &protocol);
		AHTTPRequest& setHost(const std::string &host);
		AHTTPRequest& setPort(const std::string &port);
		AHTTPRequest& setHeader(const std::string &name, const std::string &value);

		AHTTPRequest& setHeaderRaw(const std::string &HeaderRaw);
		AHTTPRequest& addToHeaderRaw(const std::string &HeaderRaw);
		std::string getHeaderRaw() const;
		bool isHeaderRawComplete() const;

		AHTTPRequest& setRequestRaw(const std::string &requestRaw);
		const std::string &getRequestRaw() const;
		AHTTPRequest& addToRequestRaw(const std::string &requestRaw);
		bool isRequestRawComplete() const;
		AHTTPRequest& clearRequestRaw();

		AHTTPRequest& setBodyRaw(const std::string &bodyRaw);
		AHTTPRequest& setQueryParams(const std::map<std::string, std::string> &queryParams);
		AHTTPRequest& setQueryParamsFromPath(const std::string &path);
		AHTTPRequest& setBodyParams(const std::map<std::string, std::string> &bodyParams);
		AHTTPRequest& setParsedBody(const std::map<std::string, std::string> &parsedBody);
		AHTTPRequest& setCookies(const std::map<std::string, std::string> &cookies);
		AHTTPRequest& setResolvedPath(const std::string &resolvedPath);
		AHTTPRequest& setSessionId(const std::string &sessionId);
		AHTTPRequest& setClientIp(const std::string &clientIp);
		
		AHTTPRequest& setUploadDir(const std::string uploadDir);
		const std::string getUploadDir() const;
		const std::string getRequestTempFilePath(std::string prefix = "") const;
		AHTTPRequest& setRequestTempFilePath(const std::string requestTempFilePath);
		AHTTPRequest& setRequestTempFilesize(size_t requestTempFilesize);
		size_t getRequestTempFilesize() const;


		AHTTPRequest& setHeaderSize(size_t header_size);
		size_t getHeaderSize() const;
		AHTTPRequest& setBodySize(size_t body_size);
		size_t getBodySize() const;

		AHTTPRequest& setClientFd(int clientFd);
		int getClientFd() const;

		AHTTPRequest& setIsCgi(bool isCgi);
		bool isCgi() const;
		AHTTPRequest& setCgiPath(const std::string &cgiPath);
		const std::string &getCgiPath() const;
		AHTTPRequest& setDocumentRoot(const std::string &documentRoot);
		const std::string &getDocumentRoot() const;

		AHTTPRequest& setMaxBodySize(size_t maxBody_size);
		size_t getMaxBodySize() const;
};