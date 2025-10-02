/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:30:07 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/08 10:49:51 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "request/AHTTPRequest.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Utils/Utils.hpp"

AHTTPRequest::AHTTPRequest() :_nullString(""), _protocol("HTTP/1.1"), _method(""), _uri(""), _path(""), _headers(), _bodyParams(),_headerRaw(""), _bodyRaw(""), _parsedBody(), _cookies(), _sessionId(""), _clientIp(""), _resolvedPath("")
, _isCgi(false), _isAllowedMethod(true) {
	_headers = std::map<std::string, std::string>();
	_requestTempFilePath = Utils::createRandomFileName();
	_requestTempFilesize = 0;
	_header_size = 0;
	_body_size = 0;
	_clientFd = -1;
	_host = "";
	_port = "";
	_queryString = "";
	_maxBody_size = 0;	
	_systemTmpDir = "/tmp/webserv/";
	_requestRaw = "";
	_documentRoot = "";
}

AHTTPRequest::~AHTTPRequest() {
}

AHTTPRequest::AHTTPRequest(const AHTTPRequest &other) {
	*this = other;
}

AHTTPRequest& AHTTPRequest::operator=(const AHTTPRequest& other) {
	if (this != &other) {
		this->_protocol = other._protocol;
		this->_method = other._method;
		this->_uri = other._uri;
		this->_path = other._path;
		this->_headers = other._headers;
		this->_bodyParams = other._bodyParams;
		this->_bodyRaw = other._bodyRaw;
		this->_parsedBody = other._parsedBody;
		this->_cookies = other._cookies;
		this->_sessionId = other._sessionId;
		this->_clientIp = other._clientIp;
		this->_resolvedPath = other._resolvedPath;
		this->_host = other._host;
		this->_port = other._port;
		this->_headerRaw = other._headerRaw;
		//this->_header_size = other._header_size;
	//	this->_tempFilePath = other._tempFilePath;
		this->_queryString = other._queryString;
		this->_uploadDir = other._uploadDir;
		this->_header_size = other._header_size;
		this->_body_size = other._body_size;
		this->_clientFd = other._clientFd;
		this->_requestTempFilePath = other._requestTempFilePath;
		this->_isCgi = other._isCgi;
		this->_isAllowedMethod = other._isAllowedMethod;
		this->_maxBody_size = other._maxBody_size;
		this->_nullString = other._nullString;
		this->_systemTmpDir = other._systemTmpDir;
		this->_requestRaw = other._requestRaw;
		this->_documentRoot = other._documentRoot;
	}
	return *this;
}

AHTTPRequest* AHTTPRequest::operator=(AHTTPRequest* other) {
	if (this != other) {
		this->_protocol = other->_protocol;
		this->_method = other->_method;
		this->_uri = other->_uri;
		this->_path = other->_path;
		this->_headers = other->_headers;
		this->_bodyParams = other->_bodyParams;
		this->_bodyRaw = other->_bodyRaw;
		this->_parsedBody = other->_parsedBody;
		this->_cookies = other->_cookies;
		this->_sessionId = other->_sessionId;
		this->_clientIp = other->_clientIp;
		this->_resolvedPath = other->_resolvedPath;
		this->_host = other->_host;
		this->_port = other->_port;
		this->_headerRaw = other->_headerRaw;
		//this->_header_size = other->_header_size;
		//this->_tempFilePath = other->_tempFilePath;
		this->_queryString = other->_queryString;
		this->_uploadDir = other->_uploadDir;
		this->_header_size = other->_header_size;
		this->_body_size = other->_body_size;
		this->_clientFd = other->_clientFd;
		this->_requestTempFilePath = other->_requestTempFilePath;
		this->_isCgi = other->_isCgi;
		this->_isAllowedMethod = other->_isAllowedMethod;
		this->_maxBody_size = other->_maxBody_size;
		this->_nullString = other->_nullString;
		this->_systemTmpDir = other->_systemTmpDir;
		this->_requestRaw = other->_requestRaw;
		this->_documentRoot = other->_documentRoot;
	}
	return this;
}

const std::string &AHTTPRequest::getMethod() const {
	return _method;
}

const std::string &AHTTPRequest::getHost() const {
	return _host;
}

const std::string &AHTTPRequest::getPort() const {
	return _port;
}

const std::string &AHTTPRequest::getUri() const {
	return _uri;
}

const std::string &AHTTPRequest::getPath() const {
	return _path;
}

const std::string &AHTTPRequest::getProtocol() const {
	return _protocol;
}

std::map<std::string, std::string> AHTTPRequest::getHeaders() const {
	return _headers;
}

const std::string &AHTTPRequest::getHeader(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator it = _headers.find(name);
	if (it != _headers.end()) {
		return it->second;
	}
	return this->_nullString;
}

std::string AHTTPRequest::getBodyRaw() const {
	return _bodyRaw;
}

std::map<std::string, std::string> AHTTPRequest::getQueryParams() const {
	return _bodyParams;
}

AHTTPRequest& AHTTPRequest::setQueryString(const std::string &queryString){

	this->_queryString = queryString;
	return *this;
}
const std::string &AHTTPRequest::getQueryString() const{
	return this->_queryString;
};

std::map<std::string, std::string> AHTTPRequest::getBodyParams() const {
	return _bodyParams;
}

std::map<std::string, std::string> AHTTPRequest::getParsedBody() const {
	return _parsedBody;
}

std::map<std::string, std::string> AHTTPRequest::getCookies() const {
	return _cookies;
}

const std::string &AHTTPRequest::getResolvedPath() const {
	return _resolvedPath;
}

/* std::string AHTTPRequest::getTempFilePath() const {
	return _tempFilePath;
} */

const std::string &AHTTPRequest::getSessionId() const {
	return _sessionId;
}

const std::string &AHTTPRequest::getClientIp() const {
	return _clientIp;
}

AHTTPRequest& AHTTPRequest::setMethod(const std::string &method) {
	_method = method;
	return *this;
}

AHTTPRequest& AHTTPRequest::setIsAllowedMethod(bool isAllowedMethod) {
	_isAllowedMethod = isAllowedMethod;
	return *this;
}

bool AHTTPRequest::isAllowedMethod() const {
	return _isAllowedMethod;
}

AHTTPRequest& AHTTPRequest::setIsAllowedMethodDelete(bool isAllowedMethodDelete) {
	_isAllowedMethodDelete = isAllowedMethodDelete;
	return *this;
}

bool AHTTPRequest::isAllowedMethodDelete() const {
	return _isAllowedMethodDelete;
}

AHTTPRequest& AHTTPRequest::setUri(const std::string &uri) {
	_uri = uri;
	return *this;
}

AHTTPRequest& AHTTPRequest::setPath(const std::string &path) {
	_path = path;
	return *this;
}

/**
 * @brief Sets the protocol of the request
 * @param protocol the protocol of the request
 * @return a reference to the current instance
 * ex: setProtocol("HTTP/1.1")
 */
AHTTPRequest& AHTTPRequest::setProtocol(const std::string &protocol) {
	_protocol = protocol;
	return *this;
}
AHTTPRequest& AHTTPRequest::setHost(const std::string &host){
	_host = host;
	return *this;
};

AHTTPRequest& AHTTPRequest::setPort(const std::string &port){
	_port = port;
	return *this;
};

/**
 * @brief Sets a header in the _headers map
 * @param name the name of the header
 * @param value the value of the header
 * @return a reference to the current instance
 * ex: setHeader("Content-Type", "application/json")
 * _headers["Content-Type"] = "application/json"
 */
AHTTPRequest& AHTTPRequest::setHeader(const std::string &name, const std::string &value) {
	_headers[name] = value;
	return *this;
}

/* AHTTPRequest& AHTTPRequest::setHeaderSize(size_t header_size) {
	_header_size = header_size;
	return *this;
}

size_t AHTTPRequest::getHeaderSize() const {
	return _header_size;
} */

AHTTPRequest& AHTTPRequest::setHeaderRaw(const std::string &HeaderRaw){
	_headerRaw = HeaderRaw;
	return *this;
};
AHTTPRequest& AHTTPRequest::addToHeaderRaw(const std::string &HeaderRaw){
	_headerRaw += HeaderRaw;
	return *this;
};
std::string AHTTPRequest::getHeaderRaw() const{
	return _headerRaw;
};
bool AHTTPRequest::isHeaderRawComplete() const{
	if (_headerRaw.find("\r\n\r\n") != std::string::npos)
		return true;
	return false;
};

/**
 * @brief Sets the raw request
 */
AHTTPRequest& AHTTPRequest::setRequestRaw(const std::string &requestRaw){
	_requestRaw = requestRaw;
	return *this;
};

const std::string &AHTTPRequest::getRequestRaw() const{
	return _requestRaw;
};

AHTTPRequest& AHTTPRequest::addToRequestRaw(const std::string &requestRaw){
	_requestRaw += requestRaw;
	return *this;
};

AHTTPRequest& AHTTPRequest::clearRequestRaw(){
	
	_requestRaw.clear();
	_requestRaw.resize(0);
	return *this;
};

bool AHTTPRequest::isRequestRawComplete() const{
	if (_requestRaw.find("\r\n\r\n") != std::string::npos)
		return true;
	return false;
};



/**
 * @brief Sets the raw body of the request
 */
AHTTPRequest& AHTTPRequest::setBodyRaw(const std::string &bodyRaw) {
	_bodyRaw = bodyRaw;
	return *this;
}

AHTTPRequest& AHTTPRequest::setQueryParams(const std::map<std::string, std::string> &queryParams) {
	_queryParams = queryParams;
	return *this;
}

/**
 * @brief Extracts query parameters from the path and stores them in the _queryParams map
 * ex: /api/user?id=42&name=nbrigui
 * _queryParams["id"] = "42"
 * _queryParams["name"] = "nbrigui"
 */
AHTTPRequest& AHTTPRequest::setQueryParamsFromPath(const std::string &path) {
	std::string query = path;
	size_t pos = query.find("?");
	if (pos != std::string::npos) {
		query = query.substr(pos + 1);
		std::istringstream ss(query);
		std::string token;
		while (std::getline(ss, token, '&')) {
			size_t pos = token.find("=");
			std::string key = token.substr(0, pos);
			std::string value = token.substr(pos + 1);
			_queryParams[key] = value;
		}
	}
	return *this;
}

AHTTPRequest& AHTTPRequest::setBodyParams(const std::map<std::string, std::string> &bodyParams) {
	_bodyParams = bodyParams;
	return *this;
}

AHTTPRequest& AHTTPRequest::setParsedBody(const std::map<std::string, std::string> &parsedBody) {
	_parsedBody = parsedBody;
	return *this;
}

AHTTPRequest& AHTTPRequest::setCookies(const std::map<std::string, std::string> &cookies) {
	_cookies = cookies;
	return *this;
}

AHTTPRequest& AHTTPRequest::setResolvedPath(const std::string &resolvedPath) {
	_resolvedPath = resolvedPath;
	return *this;
}

/* AHTTPRequest& AHTTPRequest::setTempFilePath(const std::string &tempFilePath) {
	_tempFilePath = tempFilePath;
	return *this;
} */

AHTTPRequest& AHTTPRequest::setSessionId(const std::string &sessionId) {
	_sessionId = sessionId;
	return *this;
}

AHTTPRequest& AHTTPRequest::setClientIp(const std::string &clientIp) {
	_clientIp = clientIp;
	return *this;
}


AHTTPRequest& AHTTPRequest::setUploadDir(const std::string uploadDir){
	this->_uploadDir = uploadDir;
	return *this;
}
const std::string AHTTPRequest::getUploadDir() const{
	return this->_uploadDir;
};

const std::string AHTTPRequest::getRequestTempFilePath(std::string prefix) const{
	return this->_systemTmpDir + prefix + this->_requestTempFilePath;
};

AHTTPRequest& AHTTPRequest::setRequestTempFilePath(const std::string requestTempFilePath){
	this->_requestTempFilePath = requestTempFilePath;
	return *this;
};

size_t AHTTPRequest::getRequestTempFilesize() const{
	return this->_requestTempFilesize;
};
AHTTPRequest& AHTTPRequest::setRequestTempFilesize(size_t requestTempFilesize){
	_requestTempFilesize = requestTempFilesize;
	return *this;
};

AHTTPRequest& AHTTPRequest::setHeaderSize(size_t header_size){
	_header_size = header_size;
	return *this;
};

size_t AHTTPRequest::getHeaderSize() const{
	return _header_size;
};

AHTTPRequest& AHTTPRequest::setBodySize(size_t body_size){
	_body_size = body_size;
	return *this;
};

size_t AHTTPRequest::getBodySize() const{
	return _body_size;
};

AHTTPRequest& AHTTPRequest::setClientFd(int clientFd){
	_clientFd = clientFd;
	return *this;
};

int AHTTPRequest::getClientFd() const{
	return _clientFd;
};

bool AHTTPRequest::isCgi() const{
	return _isCgi;
};

AHTTPRequest& AHTTPRequest::setIsCgi(bool isCgi){
	_isCgi = isCgi;
	return *this;
};

AHTTPRequest& AHTTPRequest::setCgiPath(const std::string &cgiPath){
	_cgiPath = cgiPath;
	return *this;
};
//"/usr/bin/php-cgi"
const std::string &AHTTPRequest::getCgiPath() const{
	return _cgiPath;
};

AHTTPRequest& AHTTPRequest::setDocumentRoot(const std::string &documentRoot){
	_documentRoot = documentRoot;
	return *this;
};

const std::string &AHTTPRequest::getDocumentRoot() const{
	return _documentRoot;
};

AHTTPRequest& AHTTPRequest::setMaxBodySize(size_t maxBody_size){
	_maxBody_size = maxBody_size;
	return *this;
};

size_t AHTTPRequest::getMaxBodySize() const{
	return _maxBody_size;
};