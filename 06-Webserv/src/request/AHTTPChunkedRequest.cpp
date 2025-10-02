/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPChunkedRequest.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:38:20 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/12 16:13:18 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request/AHTTPChunkedRequest.hpp"

AHTTPChunkedRequest::AHTTPChunkedRequest():_offsetStart(0),_offsetEnd(0),_isParsed(false),_isComplete(false),_isChunked(false){
}

AHTTPChunkedRequest::~AHTTPChunkedRequest(){
}

AHTTPChunkedRequest::AHTTPChunkedRequest(const AHTTPChunkedRequest &other){
	*this = other;
}

AHTTPChunkedRequest& AHTTPChunkedRequest::operator=(const AHTTPChunkedRequest& other) {
	if (this != &other) {
		this->_offsetStart = other._offsetStart;
		this->_offsetEnd = other._offsetEnd;
		this->_isParsed = other._isParsed;
		this->_isComplete = other._isComplete;
		this->_isChunked = other._isChunked;
		
	}
	return *this;
}

AHTTPChunkedRequest* AHTTPChunkedRequest::operator=(AHTTPChunkedRequest* other) {
	if (this != other) {
		this->_offsetStart = other->_offsetStart;
		this->_offsetEnd = other->_offsetEnd;
		this->_isParsed = other->_isParsed;
		this->_isComplete = other->_isComplete;
		this->_isChunked = other->_isChunked;
	}
	return this;
}

const std::streampos &AHTTPChunkedRequest::getOffsetStart() const {
	return _offsetStart;
}

const std::streampos &AHTTPChunkedRequest::getOffsetEnd() const {
	return _offsetEnd;
}

void AHTTPChunkedRequest::setOffsetStart(std::streampos offsetStart) {
	_offsetStart = offsetStart;
}

void AHTTPChunkedRequest::setOffsetEnd(std::streampos offsetEnd) {
	_offsetEnd = offsetEnd;
}

bool AHTTPChunkedRequest::isParsed() const {
	return _isParsed;
}

void AHTTPChunkedRequest::setIsParsed(bool isParsed) {
	_isParsed = isParsed;
}

bool AHTTPChunkedRequest::isComplete() const {
	return _isComplete;
}

void AHTTPChunkedRequest::setComplete(bool isComplete) {
	_isComplete = isComplete;
}

bool AHTTPChunkedRequest::isChunked() const {
	return _isChunked;
}

void AHTTPChunkedRequest::setChunked(bool isChunked) {
	_isChunked = isChunked;
}
