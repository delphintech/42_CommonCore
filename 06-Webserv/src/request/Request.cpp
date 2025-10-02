/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:15:03 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/05 13:08:42 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "request/Request.hpp"

Request::~Request(){
	if (_requestTempFilePath != "" && _requestTempFilePath.find(".tmp") != std::string::npos){
		remove(this->getRequestTempFilePath().c_str());
		remove(std::string(this->getRequestTempFilePath("body_")).c_str());
		remove(std::string(this->getRequestTempFilePath("output_")).c_str());
		
	}
};

Request::Request(): AHTTPRequest(),AHTTPChunkedRequest(),AMultipartRequest(){
	_forceClose = false;_isResetRevents = false;
	_timeout_value = 30000;
	_rcvbuf = 8192;
	_is_timeout = false;
	_last_active = Utils::getCurrentTimeInMilliseconds();
	_is_read_timeout = true;
	_timeout_last_read = _last_active;
}

Request::Request(const Request &other): AHTTPRequest(other),AHTTPChunkedRequest(other),AMultipartRequest(other){
	_forceClose = other.getForceClose();
	_isResetRevents = other.getIsResetRevents();
	_timeout_value = other.getTimeoutValue();
	_rcvbuf = other.getRcvbuf();
	_is_timeout = other.getIsTimeout();
	_last_active = other.getLastActive();
	_is_read_timeout = other.getIsReadTimeout();
	_timeout_last_read = other.getTimeoutLastRead();

}

Request& Request::operator=(const Request& other){
	if (this != &other) {
		AHTTPRequest::operator=(other);
		AHTTPChunkedRequest::operator=(other);		
		AMultipartRequest::operator=(other);
		this->_isResetRevents = other.getIsResetRevents();
		this->_forceClose = other.getForceClose();
		this->_timeout_value = other.getTimeoutValue();
		this->_rcvbuf = other.getRcvbuf();
		this->_is_timeout = other.getIsTimeout();
		this->_last_active = other.getLastActive();
		this->_is_read_timeout = other.getIsReadTimeout();
		this->_timeout_last_read = other.getTimeoutLastRead();
	}
	return *this;
};

Request* Request::operator=(Request* other){
	if (this != other) {
		AHTTPRequest::operator=(other);
		AHTTPChunkedRequest::operator=(other);
		AMultipartRequest::operator=(other);
		this->_isResetRevents = other->getIsResetRevents();
		this->_forceClose = other->getForceClose();
		this->_timeout_value = other->getTimeoutValue();
		this->_rcvbuf = other->getRcvbuf();
		this->_is_timeout = other->getIsTimeout();
		this->_last_active = other->getLastActive();
		this->_is_read_timeout = other->getIsReadTimeout();
		this->_timeout_last_read = other->getTimeoutLastRead();
	}
	return this;
};

Request &Request::setForceClose(bool forceClose){
	_forceClose = forceClose;
	return *this;
};

bool Request::getForceClose() const{
	return _forceClose;
};

Request &Request::setIsResetRevents(bool isResetRevents){
	_isResetRevents = isResetRevents;
	return *this;
};
bool Request::getIsResetRevents() const{
	return _isResetRevents;
};

Request *Request::clone(){
	return new Request(*this);
};
void Request::clear(){
	//std::cerr << BLUE << "[debug] Request Clear() : deleting temp file: " << _requestTempFilePath << BLUE << __FILE__ <<":"<<__LINE__ << std::endl;
	if (_requestTempFilePath != "" && _requestTempFilePath.find(".tmp") != std::string::npos){
		remove(this->getRequestTempFilePath().c_str());
		remove(std::string(this->getRequestTempFilePath("body_" )).c_str());
		remove(std::string(this->getRequestTempFilePath("output_")).c_str());
	}
	_protocol = _nullString;
	_method = _nullString;
	_uri = _nullString;
	_queryString = _nullString;
	_path = _nullString;
	_host = _nullString;
	_port = _nullString;
	_headers.clear();
	_queryParams.clear();
	_bodyParams.clear();
	_requestTempFilePath = _nullString;
	_requestTempFilesize = 0;
	_headerRaw = _nullString;
	_bodyRaw = _nullString;
	_parsedBody.clear();
	_cookies.clear();
	_sessionId = _nullString;
	_clientIp = _nullString;
	_resolvedPath = _nullString;
	_uploadDir = _nullString;
	_header_size = 0;
	_body_size = 0;
	_clientFd = 0;
	_offsetStart = 0;
	_offsetEnd = 0;
	_isParsed = false;
	_isComplete = false;
	_isChunked = false;
	_isAllowedMethod = true;
	_isResetRevents = false;
	_forceClose = false;
	_requestRaw.clear();
	_is_timeout = false;
	_is_read_timeout = true;
	//this->AHTTPRequest::setRequestTempFilePath(Utils::createRandomFileName());
};

void Request::setIsTimeout(bool is_timeout){
	_is_timeout = is_timeout;
};

bool Request::getIsTimeout() const{
	return _is_timeout;
};

void Request::setTimeoutValue(int timeout_value){
	_timeout_value = timeout_value;
};

int Request::getTimeoutValue() const{
	return _timeout_value;
};

void Request::setRcvbuf(int rcvbuf){
	_rcvbuf = rcvbuf;
};

int Request::getRcvbuf() const{
	return _rcvbuf;
};

void Request::setLastActive( time_t last_active){
	_last_active = last_active;
};

time_t Request::getLastActive() const{
	return _last_active;
};

void Request::setIsReadTimeout(bool is_read_timeout){
	_is_read_timeout = is_read_timeout;
};

bool Request::getIsReadTimeout() const{
	return _is_read_timeout;
};

void Request::setTimeoutLastRead(time_t timeout_last_read){
	_timeout_last_read = timeout_last_read;
};

time_t Request::getTimeoutLastRead() const{
	return _timeout_last_read;
};