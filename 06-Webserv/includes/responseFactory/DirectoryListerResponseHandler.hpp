/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListerResponseHandler.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:59:08 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/20 16:52:55 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef nullptr
#define nullptr NULL
#endif
#include "responseFactory/IResponseHandler.hpp"
#include <fstream>//for ifstream
#include <iostream>//for cerr and cout
#include <sys/socket.h>//for send
#include "Utils/Utils.hpp"
#include <sstream>//for stringstream
#include <dirent.h>//for DIR
#include <sys/stat.h>//for stat
#include "response/Response.hpp"
class Request;
class DirectoryListerResponseHandler : public IResponseHandler {

	private:
		Request *_req;
		std::string _file_path;
		std::string _requestPath;
		std::string _headers;
		std::string _body;

		bool _isError;
		int _errorCode;
		int _statusCode;

		std::string executeDirectoryLister();
	public:
		DirectoryListerResponseHandler(const std::string &requestPath,const std::string& file_path, Request *req);
		~DirectoryListerResponseHandler(){};

		void generateHeaders(Response *res);
		std::string getBody();

		int getStatusCode() const{return this->_statusCode;};
		void setStatusCode(int statusCode) {this->_statusCode = statusCode;};
		bool getIsError() const{return this->_isError;};
		void setErrorCode(int errCode) {this->_errorCode = errCode;this->_isError = true;};
		int getErrorCode() const{return this->_errorCode;};
};
