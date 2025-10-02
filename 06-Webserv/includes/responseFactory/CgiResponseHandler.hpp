/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandler.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:25:00 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/11 18:26:00 by nbrigui          ###   ########.fr       */
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
#include "class/File.hpp"
#include "responseFactory/Env.hpp"
class Request;
class CgiResponseHandler : public IResponseHandler {

	private:
		Request *_req;
		std::string _scriptInterpreter;
		std::string _scriptPath;
		std::string _queryString;
		std::map<std::string, std::string> _headers;
		std::multimap<std::string, std::string> _cookies;
		std::string _body;
		std::string readFromPipe(int fd);
		bool writeToPipe(int pipefd_in);
		std::string executeCGI();
		bool _isError;
		int _errorCode;
		int _statusCode;
  		std::string _reqBodyRaw;
		Env _env;
		void initEnv();
		const DomainConfig *_Dmnconfig;

	public:
		CgiResponseHandler(const std::string &scriptInterpreter, const std::string &scriptPath, Request *req);
		CgiResponseHandler(const std::string &scriptInterpreter, const std::string &scriptPath, Request *req, const DomainConfig *Dmnconfig);
		~CgiResponseHandler(){};
		void generateHeaders(Response *res);
		std::string getBody();
	//std::string executeCGI(/* const std::string &scriptPath, const std::string &queryString, const std::string& postData */);
		int getStatusCode() const{return this->_statusCode;};
		void setStatusCode(int statusCode) {this->_statusCode = statusCode;};
		bool getIsError() const{return this->_isError;};
		void setErrorCode(int errCode) {this->_errorCode = errCode;this->_isError = true;};
		int getErrorCode() const{return this->_errorCode;};
		void parseContent();

};
