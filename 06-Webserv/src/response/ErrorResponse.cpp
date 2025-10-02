/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:51:18 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/19 13:36:22 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response/ErrorResponse.hpp"

ErrorResponse::ErrorResponse(Response &res): ErrorHandler(res),_isError(false),_errorCode(0){

};

ErrorResponse::ErrorResponse(const ErrorResponse& other): ErrorHandler(other._res),_error_message(other.getErrormessage()),_isError(other.isError()),_errorCode(other.getErrorCode()){

};
ErrorResponse::~ErrorResponse(){

};

ErrorResponse &ErrorResponse::operator=(const ErrorResponse& other){
	if (this != &other) {
		ErrorHandler::operator=(other);
		this->_error_message = other.getErrormessage();
		this->_isError = other.isError();
		this->_errorCode = other.getErrorCode();
	}
	return *this;
};

bool ErrorResponse::isError() const{
	return _isError;
};

int  ErrorResponse::getErrorCode() const{
	return this->_errorCode;
};

ErrorResponse&  ErrorResponse::setError(int error){
	this->_isError = true;
	this->_errorCode = error;
	return *this;

};

const std::string &ErrorResponse::getErrormessage() const{
	return this->_error_message;
};


ErrorResponse &ErrorResponse::createErrorResponse(){
	this->getErrorPage(this->_errorCode);
	return *this;
};

ErrorResponse & ErrorResponse::mergeErrorPages(const DomainConfig& _domain_config){
	this->ErrorHandler::mergeErrorPages(_domain_config);
	return *this;
};