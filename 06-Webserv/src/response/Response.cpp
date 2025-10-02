/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:51:18 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/08 19:12:50 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response/Response.hpp"
#include "Utils/Utils.hpp"

Response::Response(): AHTTPResponse(), ChunkedResponse(), ErrorHandler(*this), ErrorResponse(*this){
	this->ErrorResponse::_isError = false;
	_sndbuf = 8192;
}

Response::~Response(){
}

Response::Response(const Response& other):AHTTPResponse(other), ChunkedResponse(other), ErrorHandler(*this), ErrorResponse(other) {
	this->ErrorResponse::_isError = other.ErrorResponse::_isError;
	this->_sndbuf = other.getSndbuf();
}

Response& Response::operator=(const Response& other){
	if (this == &other) {
		return *this;
	}
	AHTTPResponse::operator=(other);
	ChunkedResponse::operator=(other);
	ErrorResponse::operator=(other);
    ErrorHandler::operator=(other);
	this->ErrorResponse::_isError = other.ErrorResponse::_isError;
	this->_sndbuf = other.getSndbuf();
	return *this;
}

Response *Response::clone(){
	return new Response(*this);
}

std::string Response::toString() const {
	std::cout << DIM << YELLOW << "[debug] Response::toString() " RESET << __FILE__<<":"<<__LINE__ << std::endl;
	
	std::stringstream ss;
	if (_version.empty()) {
		ss << "HTTP/1.1 ";
	} else {
		ss << _version << " ";
	}
	if (_status_message == "") {	
		ss << _status_code << " " << this->ErrorHandler::getErrorMessage(_status_code).error_message << "\r\n";	
	} else
		ss << _status_code << " " << _status_message << "\r\n";
	bool is_header_set = false;
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
		ss << it->first << ": " << it->second << "\r\n";
		is_header_set = true;
	}
	if (this->isError()) {
		ss << "Content-Type: text/html\r\n";
	}
	//Set-Cookie: sessionId=abc123; Expires=Wed, 09 Jun 2021 10:18:14 GMT; Max-Age=3600; Domain=example.com; Path=/; Secure; HttpOnly; SameSite=Strict
	//@Todo class Cookies
	for (std::map<std::string, std::string>::const_iterator it = _cookies.begin(); it != _cookies.end(); ++it) {
		ss << "Set-Cookie: " << it->first << "=" << it->second << "; Max-Age=3600; Domain=127.0.0.1; Path=/; SameSite=Strict\r\n";
		is_header_set = true;
	}
	if (is_header_set) {
		ss << "\r\n";
	}
	ss << _body;
	//debug print
	std::cout << "**** [debug] response size: " << ss.str().size() << std::endl<< std::endl;
	std::cout << DIM << YELLOW << "[debug] END Response::toString() " RESET << __FILE__<<":"<<__LINE__ << std::endl;

	return ss.str();
}

std::string Response::generateHeader()const {
	std::stringstream ss;
	if (_version.empty()) {
		ss << "HTTP/1.1 ";
	} else {
		ss << _version << " ";
	}
	if (_status_message == "") {	
		ss << _status_code << " " << this->ErrorHandler::getErrorMessage(_status_code).error_message << "\r\n";	
	} else
		ss << _status_code << " " << _status_message << "\r\n";
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
		ss << it->first << ": " << it->second << "\r\n";
	}
	for (std::map<std::string, std::string>::const_iterator it = _cookies.begin(); it != _cookies.end(); ++it) {
		ss << "Set-Cookie: " << it->first << "=" << it->second << "; Max-Age=3600; Domain=127.0.0.1; Path=/; SameSite=Strict\r\n";
	}
	ss << "\r\n";
	return ss.str();
}

std::string Response::getBody() const {
	return _body;
}

std::string Response::getBody(ssize_t offsetstart,ssize_t size){
	std::string body = "";
	if (size == 0)
		body = _body.substr(offsetstart);
	else
		body = _body.substr(offsetstart, size);
	return body;
};

/**
 * generate the response string
 */
/* Response &Response::setResponse(){
	_response = this->toString();
	return *this;
} */

void Response::clear(){

	_error_code = 0;
	_version = "HTTP/1.1";
	_status_code = 0;
	_status_message = "";
	_headers.clear();
	_cookies.clear();
	_body = "";
	_error_pages.clear();
	_jsonStringData = "";
	_jsonData.clear();
	_isCGI = false;
	_isError = false;
	_errorCode = 0;
	 _isComplete = false;
	_isGenerated = false;
	_isChunked = false;
	_chunkedHeader = "";
	_chunkedHeaderSize = 0;
	_isHeaderSent = false;
	_bodyPathFile = "";
	_bodySize = 0;
	_offsetstart = 0;
	_offsetSend = 0;
	_bufferSize = 4096;
}

int Response::getSndbuf() const {
	return _sndbuf;
}

Response& Response::setSndbuf(int sndbuf) {
	_sndbuf = sndbuf;
	return *this;
}