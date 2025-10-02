/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticFileResponseHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:30:07 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/07 10:33:05 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "responseFactory/StaticFileResponseHandler.hpp"
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
StaticFileResponseHandler::StaticFileResponseHandler(const std::string &requestPath,const std::string& file_path, Request *req)
	:_req(req), _filePath(file_path),_requestPath(requestPath), _isError(false) {

};

void StaticFileResponseHandler::generateHeaders(Response *res) {
	if (this->getIsError()) {
		res->setError(this->getErrorCode());
		return;
	}
	//res->setHeader(this->_headers);
	if (this->_cookies.size() > 0)
		res->setCookie(this->_cookies);
	res->setVersion().setStatusCode(this->getStatusCode())
	.setHeader("Content-Length", _body.size())
	.setContentType(Utils::getMimeType(_filePath))
	.setKeepAlive(_req->getHeader("Connection") != "close");
	_req->getMethod() == "HEAD" ? res->setBody("") : res->setBody(_body);
	
} 

std::string StaticFileResponseHandler::getFileContent(std::string path) {
	std::ifstream file(path.c_str(), std::ios::binary);
	this->_isChunked = false;
	//binary garanti que le fichier est lu byte par byte
	if (!file.is_open()) {
			std::cerr << "Failed to open file: " << _filePath << std::endl;
			this->setErrorCode(404);
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}

std::string StaticFileResponseHandler::getBody() {
	this->_body = executeStaticFile();
	return _body;
}

/**
 * chunked
 */
std::string StaticFileResponseHandler::getFileContent(std::string path, const std::streampos &offset) {
	//1- ouvrir le fichier
	std::ifstream file_stream(path.c_str(), std::ios::binary);
	//binary garanti que le fichier est lu byte par byte
	if (!file_stream.is_open()) {
			std::cerr << "Failed to open file: " << _filePath << std::endl;
			this->setErrorCode(404);
		return "";
	}

	//2- lire le fichier
	//const size_t CHUNK_SIZE = 4096;
	const size_t CHUNK_SIZE = 4096;
	char buffer[CHUNK_SIZE];
	file_stream.seekg(offset);
    file_stream.read(buffer, CHUNK_SIZE);
    std::streamsize bytes_read = file_stream.gcount();

	//3- fermer le fichier
	file_stream.close();

	// Construire et envoyer le chunk
	std::stringstream chunk_stream;
	chunk_stream << std::hex << bytes_read << "\r\n";
	chunk_stream.write(buffer, bytes_read);
	chunk_stream << "\r\n";

	std::string chunk = chunk_stream.str();
	// Mettre à jour l'offset
	_req->setOffsetStart(offset + bytes_read);
	//si on lit 0 bytes, on a atteint la fin du fichier
	if (bytes_read > 0) {
		this->_isChunked = true;
	}
	else{
		this->_isChunked = false;
	}
	return chunk;
}

std::string StaticFileResponseHandler::executeStaticFile() {
	std::ifstream file(_filePath.c_str(), std::ios::binary);
	/* if (!file.is_open()) {
		std::cerr << "Failed to open file: " << _file_path << std::endl;
		return "";
	}
	file.close(); */
		//file size
	std::streampos size = 0;
	std::ifstream file_size(_filePath.c_str(), std::ios::binary);
	if (file_size.is_open()) {
		file_size.seekg(0, std::ios::end);
		size = file_size.tellg();
		file_size.close();
	}

	std::string content;
	std::streampos sizeTestEnd = 8196;
/* 	if (size == _offset)
	{		
		Log::logMsg(GREEN, "_offset: %d", static_cast<int>(_offset));
		_isChunked = false;
		return "\r\n";

	} */
	if (0 && size > sizeTestEnd) {// non utilisé
		content = getFileContent(_filePath, _req->getOffsetStart());
	}else{
		content = getFileContent(_filePath);
	}
	if (content.empty()) {
		this->setStatusCode(200);
		return "";
	}
	this->setStatusCode(200);
	return content;
}

