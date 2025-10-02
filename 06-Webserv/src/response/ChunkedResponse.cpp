/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:51:18 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/22 14:58:40 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response/ChunkedResponse.hpp"
#include "class/File.hpp"
#include "Utils/Utils.hpp"
#include <iostream>

ChunkedResponse::ChunkedResponse() : _isComplete(false), _isGenerated(false), _isChunked(false), _chunkedHeader(""), _chunkedHeaderSize(0), _isHeaderSent(false), _bodyPathFile(""), _bodySize(0)
{
	_offsetSend = 0;
	_offsetstart = 0;
	_bufferSize = 4096;	
}

ChunkedResponse::~ChunkedResponse()
{
//	std::cout << DIM << YELLOW << "[debug] ChunkedResponse::~ChunkedResponse() " RESET << __FILE__<<":"<<__LINE__ << std::endl;
}

ChunkedResponse& ChunkedResponse::operator=(const ChunkedResponse& other) {
	if (this == &other) {
		return *this;
	}
	_isComplete = other._isComplete;
	_isGenerated = other._isGenerated;
	_isChunked = other._isChunked;
	_chunkedHeader = other._chunkedHeader;
	_chunkedHeaderSize = other._chunkedHeaderSize;
	_isHeaderSent = other._isHeaderSent;
	_bodyPathFile = other._bodyPathFile;
	_bodySize = other._bodySize;
	_offsetstart = other._offsetstart;
	_offsetSend = other._offsetSend;
	_bufferSize = other._bufferSize;
	return *this;
}

ChunkedResponse& ChunkedResponse::setChunked(bool chunked) {
	_isChunked = chunked;
	return *this;
}

ChunkedResponse& ChunkedResponse::setChunkedHeader(const std::string& header) {
	_chunkedHeader = header;
	_chunkedHeaderSize = header.size();	
	return *this;
}

ChunkedResponse& ChunkedResponse::setBodyPathFile(const std::string& bodyPathFile) {
	_bodyPathFile = bodyPathFile;
	return *this;
}

ChunkedResponse& ChunkedResponse::setOffsetStart(ssize_t offsetstart) {
	this->_offsetstart = offsetstart;
	return *this;
}

ChunkedResponse& ChunkedResponse::setBufferSize(int bufferSize) {
	this->_bufferSize = bufferSize;
	return *this;
}

bool ChunkedResponse::isComplete()const {
	return _isComplete;
}

bool ChunkedResponse::isGenerated()const {
	return _isGenerated;
}

bool ChunkedResponse::isChunked()const {
	return _isChunked;
}

std::string ChunkedResponse::getChunkedHeader()const {
	return _chunkedHeader;
}

std::string ChunkedResponse::getBodyPathFile()const {
	return _bodyPathFile;
}

ssize_t ChunkedResponse::getOffsetStart()const {
	return _offsetstart;
}

int ChunkedResponse::bufferSize()const {
	return _bufferSize;
}

std::string ChunkedResponse::getContent() {
	if (this->_bodyPathFile == "") {
		std::cerr << "no body: " << _bodyPathFile << std::endl;
		return "";
	}
	File bodyFile(this->_bodyPathFile);	
	return bodyFile.getContent();
}

std::string ChunkedResponse::getContent(ssize_t offsetstart) {
	if (this->_bodyPathFile == "") {
		std::cerr << "no body: " << _bodyPathFile << std::endl;
		return "";
	}
	File bodyFile(this->_bodyPathFile);	
	return bodyFile.getContent(offsetstart, this->_bufferSize);
}
std::string ChunkedResponse::getContent(ssize_t offsetstart, ssize_t size) {
	if (this->_bodyPathFile == "") {
		std::cerr << "no body: " << _bodyPathFile << std::endl;
		return "";
	}
	File bodyFile(this->_bodyPathFile);	
	return bodyFile.getContent(offsetstart, size);
}
ssize_t ChunkedResponse::getBodySize() const {
	return _bodySize;
}

ssize_t ChunkedResponse::getChunkedHeaderSize() const {
	return _chunkedHeaderSize;
}

bool ChunkedResponse::isHeaderSent() const {
	return _isHeaderSent;
}

ChunkedResponse& ChunkedResponse::setHeaderSent(bool isHeaderSent) {
	_isHeaderSent = isHeaderSent;
	return *this;
}

ChunkedResponse& ChunkedResponse::setBodySize(ssize_t bodySize) {
	_bodySize = bodySize;
	return *this;
}

ChunkedResponse& ChunkedResponse::setChunkedHeaderSize(ssize_t chunkedHeaderSize) {
	_chunkedHeaderSize = chunkedHeaderSize;
	return *this;
}

ChunkedResponse& ChunkedResponse::setComplete(bool isComplete) {
	_isComplete = isComplete;
	return *this;
}

ChunkedResponse& ChunkedResponse::setGenerated(bool isGenerated) {
	_isGenerated = isGenerated;
	return *this;
}

