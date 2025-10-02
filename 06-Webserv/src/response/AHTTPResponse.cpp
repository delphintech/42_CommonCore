/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:51:18 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/05 15:06:16 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response/AHTTPResponse.hpp"
#include "Utils/Utils.hpp"

AHTTPResponse::AHTTPResponse() : _error_code(0), _version("HTTP/1.1"), _status_code(0){
	_status_message = "";
	_headers = std::map<std::string, std::string>();
	_cookies = std::multimap<std::string, std::string>();
	_body = "";
	_error_pages = std::map<int, std::string>();
	_jsonStringData = "";
	_jsonData = std::map<std::string, std::string>();
	_isCGI = false;
	_sokeepalive_time = 1000; // 1s
	_sokeepalive_intvl = 100; // 100 iters

}

AHTTPResponse::AHTTPResponse(const AHTTPResponse& other) {
	_error_code = other._error_code;
	_version = other._version;
	_status_code = other._status_code;
	_status_message = other._status_message;
	_headers = other._headers;
	_cookies = other._cookies;
	_body = other._body;
	_error_pages = other._error_pages;
	_jsonStringData = other._jsonStringData;
	_jsonData = other._jsonData;
	_isCGI = other._isCGI;
	_sokeepalive_time = other._sokeepalive_time;
	_sokeepalive_intvl = other._sokeepalive_intvl;
}

AHTTPResponse::~AHTTPResponse(){
//	std::cout << DIM << YELLOW << "[debug] AHTTPResponse::~AHTTPResponse() " RESET << __FILE__<<":"<<__LINE__ << std::endl;
}

AHTTPResponse& AHTTPResponse::operator=(const AHTTPResponse& other) {
	if (this == &other) {
		return *this;
	}
	_error_code = other._error_code;
	_version = other._version;
	_status_code = other._status_code;;
	_status_message = other._status_message;;
	_headers = other._headers;
	_cookies = other._cookies;
	_body = other._body;
	_error_pages = other._error_pages;;
	_jsonStringData = other._jsonStringData;;
	_jsonData = other._jsonData;;
	_isCGI = other._isCGI;
	_sokeepalive_time = other._sokeepalive_time;
	_sokeepalive_intvl = other._sokeepalive_intvl;
	return *this;
}

AHTTPResponse& AHTTPResponse::setVersion(const std::string& version) {
	_version = version;
	return *this;

}

AHTTPResponse& AHTTPResponse::setStatusCode(int status_code) {
	_status_code = status_code;
	return *this;
}

AHTTPResponse& AHTTPResponse::setStatusMessage(const std::string& status_message) {
	_status_message = status_message;
	return *this;
}

AHTTPResponse& AHTTPResponse::setContentType(const std::string& content_type) {
	_headers.insert(std::pair<std::string, std::string>("Content-Type", content_type));
	return *this;
}

AHTTPResponse& AHTTPResponse::setContentLength(size_t content_length) {
	_headers.insert(std::pair<std::string, std::string>("Content-Length", Utils::String::intToString(content_length)));
	return *this;
}

AHTTPResponse& AHTTPResponse::setKeepAlive(bool keep_alive) {
	if (keep_alive) {
		_headers.insert(std::pair<std::string, std::string>("Connection", "keep-alive"));
		_headers.insert(std::pair<std::string, std::string>("Keep-Alive", "timeout=" + Utils::String::intToString(_sokeepalive_time) + ", max=" + Utils::String::intToString(_sokeepalive_intvl)));
	} else {
		_headers.insert(std::pair<std::string, std::string>("Connection", "close"));
	}
	return *this;
}

AHTTPResponse& AHTTPResponse::setHeader(std::map<std::string, std::string> &headers) {
	if (_headers.empty()) {
		_headers = headers;
	}
	else {
		_headers.insert(headers.begin(), headers.end());
	}
	return *this;
}
AHTTPResponse& AHTTPResponse::setHeader(const std::map<std::string, std::string> &headers) {
	if (_headers.empty()) {
		_headers = headers;
	}
	else {
		_headers.insert(headers.begin(), headers.end());
	}
	return *this;
}
AHTTPResponse& AHTTPResponse::setHeader(const std::string& name, const std::string& value) {
	_headers.insert(std::pair<std::string, std::string>(name, value));
	return *this;
}
AHTTPResponse& AHTTPResponse::setHeader(const std::string& name, int value) {
	_headers.insert(std::pair<std::string, std::string>(name, Utils::String::intToString(value)));
	return *this;
}

AHTTPResponse& AHTTPResponse::setCookie(std::multimap<std::string, std::string> &cookies) {
	_cookies = cookies;
	return *this;
}
AHTTPResponse& AHTTPResponse::setCookie(const std::string& name, const std::string& value) {
	_cookies.insert(std::pair<std::string, std::string>(name, value));
	return *this;
}
AHTTPResponse& AHTTPResponse::setCookie(const std::string& name, int value) {
	_cookies.insert(std::pair<std::string, std::string>(name, Utils::String::intToString(value)));
	return *this;
}

AHTTPResponse& AHTTPResponse::setBody(const std::string& body) {
	_body = body;
	return *this;
}

bool AHTTPResponse::isCGI()const {
	return this->_isCGI;
};
AHTTPResponse& AHTTPResponse::setisCGI(bool isCGI){
	this->_isCGI = isCGI;
	return *this;
};

int AHTTPResponse::getStatusCode() const{
	return _status_code;
};

std::string &AHTTPResponse::erase(ssize_t size) {
	if (size < 0)
		return _body;
	else if (size > static_cast<ssize_t> (_body.size()))
		_body = "";
	else
		_body.erase(0, size);
	return _body;
}

int AHTTPResponse::getSoKeepaliveTime() const {
	return _sokeepalive_time;
}

AHTTPResponse& AHTTPResponse::setSoKeepaliveTime(int sokeepalive_time) {
	_sokeepalive_time = sokeepalive_time;
	return *this;
}

int AHTTPResponse::getSoKeepaliveIntvl() const {
	return _sokeepalive_intvl;
}

AHTTPResponse& AHTTPResponse::setSoKeepaliveIntvl(int sokeepalive_intvl) {
	_sokeepalive_intvl = sokeepalive_intvl;
	return *this;
}

AHTTPResponse& AHTTPResponse::decrementCountMaxKeepAlive() {
	_sokeepalive_intvl -= 1;
	return *this;
}
