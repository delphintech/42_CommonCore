/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMultipartRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:29:48 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/02 12:47:34 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request/AMultipartRequest.hpp"

AMultipartRequest::~AMultipartRequest() {}

AMultipartRequest& AMultipartRequest::setFormData(const std::string& name, const FormData& data) {
	_form_data[name] = data;
	return *this;
}

std::map<std::string,AMultipartRequest::FormData > AMultipartRequest::getFormDatas() const {
	return _form_data;
}

AMultipartRequest& AMultipartRequest::setFormDatas(const std::map<std::string,FormData >& form_data) {
	_form_data = form_data;
	return *this;
}

AMultipartRequest& AMultipartRequest::addFormData(const std::string& name, const FormData& data) {
	_form_data[name] = data;
	return *this;
}
#include <iostream>
AMultipartRequest& AMultipartRequest::addFormData(const std::string& name, std::string data, std::string content_type, std::string filename) {
	//debug print form data size 
	//std::cerr << "Form data size: " << _form_data.size() << std::endl;
	FormData formData = { "", "", "", "" };
	formData.name = name;
	formData.data = data;
	formData.content_type = content_type;
	formData.filename = filename;
	_form_data[name] = formData;
	return *this;
}

AMultipartRequest& AMultipartRequest::clearFormData() {
	_form_data.clear();
	return *this;
}

AMultipartRequest::FormData AMultipartRequest::getFormData(const std::string& name) const {
	std::map<std::string,FormData >::const_iterator it = _form_data.find(name);
	if (it != _form_data.end()) {
		return it->second;
	}
	return FormData();
}

AMultipartRequest& AMultipartRequest::operator=(const AMultipartRequest& other) {
	if (this == &other) {
		return *this;
	}
	_form_data = other._form_data;
	return *this;
}
AMultipartRequest* AMultipartRequest::operator=(AMultipartRequest* other) {
	if (this == other) {
		return this;
	}
	_form_data = other->_form_data;
	return this;
}
AMultipartRequest& AMultipartRequest::setBoundary(const std::string& boundary) {
	_boundary = boundary;
	return *this;
}

std::string AMultipartRequest::getBoundary() const {
	return _boundary;
}

AMultipartRequest& AMultipartRequest::setIsMultipart(bool isMultipart) {
	_isMultipart = isMultipart;
	return *this;
}

bool AMultipartRequest::isMultipart() const {
	return _isMultipart;
}