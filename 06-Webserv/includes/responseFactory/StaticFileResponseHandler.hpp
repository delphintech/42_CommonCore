/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticFileResponseHandler.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:25:00 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/20 16:51:47 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#ifndef nullptr
# define nullptr NULL
#endif
#include "responseFactory/IResponseHandler.hpp"
#include <fstream>//for ifstream
#include <iostream>//for cerr and cout
#include <sys/socket.h>//for send
#include <sstream>//for stringstream
#include <dirent.h>//for DIR
#include <sys/stat.h>//for stat

#include "response/Response.hpp"
class Request;
class StaticFileResponseHandler : public IResponseHandler {

	private:
		Request *_req;
		std::string _filePath;
		std::string _requestPath;
		std::string _queryString;
		bool _isChunked;
		std::map<std::string, std::string> _headers;
		std::multimap<std::string, std::string> _cookies;
		std::string _body;
		std::string executeStaticFile();
		std::string getFileContent(std::string path);
		std::string getFileContent(std::string path,const std::streampos &offset);
		bool _isError;
		int _errorCode;
		int _statusCode;

	public:
		StaticFileResponseHandler(const std::string &requestPath,const std::string& file_path, Request *req);
		~StaticFileResponseHandler(){};
		void generateHeaders(Response *res);
		std::string getBody();

		int getStatusCode() const{return this->_statusCode;};
		void setStatusCode(int statusCode) {this->_statusCode = statusCode;};
		bool getIsError() const{return this->_isError;};
		void setErrorCode(int errCode) {this->_errorCode = errCode;this->_isError = true;};
		int getErrorCode() const{return this->_errorCode;};
};
