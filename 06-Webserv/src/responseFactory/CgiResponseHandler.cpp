/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:30:07 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/07 10:33:05 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responseFactory/CgiResponseHandler.hpp"
#include "responseFactory/Env.hpp" 
#include "response/Response.hpp"
#include <fstream>//for ifstream
#include <iostream>//for cerr and cout
#include <sys/socket.h>//for send
#include <sstream>//for stringstream
//#include "Mime.hpp"
#include <dirent.h>//for DIR
#include <sys/stat.h>//for stat
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>//
#include <stdlib.h>//setenv
#include <sys/resource.h>//for rlimit
#include <pwd.h>//for getpwnam
#include "request/Request.hpp"
#include "Utils/Utils.hpp"

/*std::string scriptInterpreter ="/usr/bin/php-cgi";*/
CgiResponseHandler::CgiResponseHandler(const std::string &scriptInterpreter, const std::string &scriptPath, Request *req)
	:_req(req),_scriptInterpreter(scriptInterpreter), _scriptPath(scriptPath),_queryString(""), _isError(false){
		//std::cerr << "[debug] CgiResponseHandler::CgiResponseHandler() : Constructor " <<__FILE__ << ":"<< __LINE__ << std::endl;
};
CgiResponseHandler::CgiResponseHandler(const std::string &scriptInterpreter, const std::string &scriptPath, Request *req,const DomainConfig *Dmnconfig)
	:_req(req),_scriptInterpreter(scriptInterpreter), _scriptPath(scriptPath),_queryString(""), _isError(false){
	_Dmnconfig = Dmnconfig;
};
void CgiResponseHandler::generateHeaders(Response *res) {
//	std::cerr << "[debug] CgiResponseHandler::generateHeaders() : Generating headers " <<__FILE__ << ":"<< __LINE__ << std::endl;
	if (this->getIsError()) {
		res->setError(this->getErrorCode());
		return;
	}
	res->setHeader(this->_headers);
	if (this->_cookies.size() > 0)
		res->setCookie(this->_cookies);
	if (_headers.find("Content-Length") == _headers.end())
		res->setHeader("Content-Length", _body.size());
	res->setVersion().setStatusCode(this->getStatusCode())
	.setContentType("text/html; charset=utf-8")
	.setKeepAlive(_req->getHeader("Connection") != "close");
	_req->getMethod() == "HEAD" ? res->setBody("") : res->setBody(_body);
	res->setBodyPathFile(_req->getRequestTempFilePath("output_"));
} 
	
std::string CgiResponseHandler::getBody() {
//	std::cerr << "[debug] CgiResponseHandler::getBody() : Getting body " <<__FILE__ << ":"<< __LINE__ << std::endl;
	executeCGI();
	return _body;
}

#include "responseFactory/StaticFileResponseHandler.hpp"
bool CgiResponseHandler::writeToPipe(int pipefd_in) {
//	std::cerr << "[debug] CgiResponseHandler::writeToPipe() : Writing to pipe " <<__FILE__ << ":"<< __LINE__ << std::endl;
	//recurcive call to write to pipe
	File bodyFile(std::string(_req->getRequestTempFilePath("body_")).c_str());

	const size_t bufferSize = 4096;
	std::streampos offsetStart = 0;
	while (true) {
		std::string content = bodyFile.getContent(offsetStart, bufferSize);
		ssize_t bytesRead = content.size();
		offsetStart = offsetStart + bytesRead;
		if (bytesRead == 0) {
			break;
		}
		if (write(pipefd_in, content.c_str(), bytesRead) == -1) {
			std::cerr << "[error] Failed to write to pipe" << std::endl;
			return false;
		}
	}
//	std::cerr << "[debug] CgiResponseHandler::writeToPipe() : Wrote to pipe ok" <<__FILE__ << ":"<< __LINE__ << std::endl;
	return true;
}

void CgiResponseHandler::initEnv(){
//	std::cerr << "[debug] CgiResponseHandler::initEnv() " <<__FILE__ << ":"<< __LINE__ << std::endl;
	File bodyFile(std::string(_req->getRequestTempFilePath("body_")).c_str());
	//_reqBodyRaw = bodyFile.getContent();	
	_env.add("GATEWAY_INTERFACE", "CGI/1.1");
	_env.add("DOCUMENT_ROOT", _req->getDocumentRoot().c_str());
	_env.add("SERVER_PROTOCOL", _req->getProtocol().c_str());
	_env.add("SCRIPT_FILENAME", _scriptPath.c_str());
	_env.add("SCRIPT_NAME", _scriptPath.c_str());
	_env.add("PATH_INFO", _req->getPath());
	_env.add("REQUEST_METHOD", _req->getMethod().c_str());
	_env.add("CONTENT_TYPE", _req->getHeader("Content-Type").c_str());
//	std::cerr << "[debug] CgiResponseHandler::initEnv() : CONTENT_TYPE " << _req->getHeader("Content-Type").c_str() << "  " <<__FILE__ << ":"<< __LINE__ << std::endl;
	if (_req->getHeader("Content-Length") != "" )
		_env.add("CONTENT_LENGTH", _req->getHeader("Content-Length").c_str());
	else
		//_env.add("CONTENT_LENGTH", Utils::String::intToString(_reqBodyRaw.size()).c_str());
		_env.add("CONTENT_LENGTH", Utils::String::intToString(bodyFile.getSize()).c_str());
	_env.add("QUERY_STRING",  _req->getQueryString().c_str());
	_env.add("REDIRECT_STATUS", "200");
	_env.add("REQUEST_URI", _req->getUri().c_str()); 
	_env.add("SERVER_NAME", "127.0.0.1");
	_env.add("REMOTE_USER", "nbrigui");
	_env.add("HTTP_ACCEPT",  _req->getHeader("Accept").c_str());//_env.add("HTTP_ACCEPT", "multipart/form-data, application/json");
	_env.add("HTTP_REFERER",  _req->getHeader("Referer").c_str());
	_env.add("HTTP_COOKIE",  _req->getHeader("Cookie").c_str());
	_env.add("UPLOAD_DIR", _req->getUploadDir().c_str());
	_env.add("HTTP_USER_AGENT",  _req->getHeader("User-Agent").c_str());

	//iterate over headers
//	std::cerr << YELLOW << "[debug] CgiResponseHandler::initEnv() : Iterating over headers " <<__FILE__ << ":"<< __LINE__ << std::endl;
	if (_req->getHeaders().size() > 0){
		std::map<std::string, std::string> headers = _req->getHeaders();
		for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); ++it) {
			if(it->first.find("X-") != std::string::npos)//if the header starts with X_ :X is a non-standard header
			{
				std::string headerKey = "HTTP_" + Utils::String::toUpper(it->first);
				std::replace(headerKey.begin(), headerKey.end(), '-', '_');
				_env.add(headerKey, it->second.c_str());
			}
		}
	}
//	std::cerr << YELLOW << "[debug] CgiResponseHandler::initEnv() : Iterating over headers "<<RESET <<__FILE__ << ":"<< __LINE__ << std::endl;
}

#include "class/PollManager.hpp"
std::string CgiResponseHandler::executeCGI() {
//	std::cerr << BLUE <<"[debug] CgiResponseHandler::executeCGI() : Executing CGI " << RESET <<__FILE__ << ":"<< __LINE__ << std::endl;
	std::map<std::string, std::string> postData;
	int pipeFd[2];
   	File bodyOtput = File(std::string(_req->getRequestTempFilePath("output_")).c_str());
	bodyOtput.openWriteFile();
//	std::cerr << "[debug] CgiResponseHandler::executeCGI() : Opening output file " <<__FILE__ << ":"<< __LINE__ << std::endl;
	long fdOut = bodyOtput.getFd();
	if (pipe(pipeFd) != 0)
		return "Internal Server Error";
	// Initialize the environment
	this->initEnv();
	// Fork the process
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		std::cerr << "fork" << std::endl;
		this->setErrorCode(500);
		return "Internal Server Error";
	}	
	// Conversion de l'environnement pour execve()
	std::vector<char*> envArray = _env.toEnvArray();
	if (pid == 0) { // Child process
		alarm(_Dmnconfig->getSendTimeout());
	//	std::cerr << "[debug] CgiResponseHandler::executeCGI() : Child process " <<__FILE__ << ":"<< __LINE__ << std::endl;
		close(pipeFd[1]);
		dup2(pipeFd[0], STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		close(pipeFd[0]);
		// Préparer les arguments pour execve()		
		char* args[] = {
			const_cast<char*>(_scriptInterpreter.c_str()),
			const_cast<char*>(_scriptPath.c_str()),
			nullptr
			};

		//std::cerr << YELLOW <<"[debug] CgiResponseHandler::execve() : Executing CGI script"<< RESET<<" " <<__FILE__ << ":"<< __LINE__ << std::endl;
		// Execute the CGI script
		execve(_scriptInterpreter.c_str(), args, envArray.data());
		alarm(0);
		_env.cleanEnvArray(envArray);
		perror("execve");
		std::cerr << "execve" << std::endl;
		exit(EXIT_FAILURE);
	} else { // Parent process
		close(pipeFd[0]);
		//write the body to the pipe
		if (_req->getMethod() == "POST" || _req->getMethod() == "PUT")
			this->writeToPipe(pipeFd[1]);
		close(pipeFd[1]);
		int status;
		waitpid(pid, &status, 0);
		//close the Output file
		bodyOtput.closeFile(); //close the file descriptor == ( close(fdOut); fdOut = -1;)
		_env.cleanEnvArray(envArray);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
			std::cerr << "CGI script exited with status " << WEXITSTATUS(status) << std::endl;
			this->setErrorCode(500);
			return "Internal Server Error";
		} else if (WIFSIGNALED(status)) {
			if (WTERMSIG(status) == SIGALRM) {
				std::cerr << "CGI script killed due to timeout" << std::endl;
				this->setErrorCode(504);//Gateway Timeout
			} else {
				std::cerr << "CGI script killed by signal " << WTERMSIG(status) << std::endl;
				this->setErrorCode(500);
			}
		}
		//set the status code
		if (_req->getMethod() == "POST")
			this->setStatusCode(201);
		if (_req->getMethod() == "GET" || _req->getMethod() == "HEAD")
			this->setStatusCode(200);
		if (_req->getMethod() == "PUT")
			this->setStatusCode(204);
		if (_req->getMethod() == "DELETE")
			this->setErrorCode(204);
		std::cerr << GREEN <<"CGI script executed successfully for client "<< _req->getClientFd() << RESET << std::endl;
	
		//read the output file , set the content parsed to _body abd return the content
		File outputFile(std::string(_req->getRequestTempFilePath("output_")).c_str());
		_body = outputFile.getContent();
		this->parseContent();
		return _body.c_str();
	}
}


/**
 * Extracts the headers and body from the CGI output
 * sets the headers and body
 *  
 */
void CgiResponseHandler::parseContent() {
	//std::cerr << "[debug] CgiResponseHandler::extractHeader() : Extracting header " <<__FILE__ << ":"<< __LINE__ << std::endl;
	bool isHeaderCarriageReturn = true;
	std::string headerRaw;

	size_t pos = _body.find("\r\n\r\n");
	if (pos == std::string::npos) {
		pos = _body.find("\n\n");
		isHeaderCarriageReturn = false;
	}
	if (pos != std::string::npos) {
		int offset = isHeaderCarriageReturn ? 4 : 2;
		headerRaw = _body.substr(0, pos + offset);
		_body.erase(0, pos + offset);
	} 

	if (!headerRaw.empty()) {
		std::istringstream headerStream(headerRaw);
		std::string line;
		while (std::getline(headerStream, line)) {
			size_t pos = line.find(": ");
			if (pos != std::string::npos) {
				std::string key = Utils::normalizeHeaderName(line.substr(0, pos));
				std::string value = line.substr(pos + 2);
				if (key == "Set-Cookie") {
					std::string cookie = value.substr(0, value.find(";"));
					std::string cookieName = cookie.substr(0, cookie.find("="));
					std::string cookieValue = cookie.substr(cookie.find("=") + 1);
					_cookies.insert(std::pair<std::string, std::string>(cookieName, cookieValue));
				} else {
					if (key != "" && key != "Content-Type" && key != "Status")
						_headers.insert(std::pair<std::string, std::string>(key, value));
				}
			}
		}
	}
}