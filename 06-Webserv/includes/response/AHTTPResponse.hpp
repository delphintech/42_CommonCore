/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPResponse.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:53:27 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/05 15:06:40 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>//std::stringstream

class AHTTPResponse 
{
	protected:
		int _error_code;
		std::string _version;
		int _status_code;
		std::string _status_message;
		std::map<std::string, std::string> _headers;
		std::multimap<std::string, std::string> _cookies;
		std::string _body;
		std::map<int,std::string> _error_pages;
		std::string _jsonStringData;
		std::map<std::string, std::string> _jsonData;
		int _sokeepalive_time;
		int _sokeepalive_intvl;

		bool _isCGI;

	public:
		AHTTPResponse();
		AHTTPResponse(const AHTTPResponse& other);
		virtual ~AHTTPResponse();
		AHTTPResponse& operator=(const AHTTPResponse& other);
		AHTTPResponse& setVersion(const std::string& version = "HTTP/1.1");
		AHTTPResponse& setStatusCode(int status_code = 200);
		AHTTPResponse& setStatusMessage(const std::string& status_message = "OK");
		AHTTPResponse& setContentType(const std::string& content_type = "text/html");
		AHTTPResponse& setContentLength(size_t content_length);
		AHTTPResponse& setKeepAlive(bool keep_alive = false);
		AHTTPResponse& setHeader(std::map<std::string, std::string> &headers);
		AHTTPResponse& setHeader(const std::map<std::string, std::string> &headers);
		AHTTPResponse& setHeader(const std::string& name, const std::string& value);
		AHTTPResponse& setHeader(const std::string& name, int value);
		AHTTPResponse& setCookie(std::multimap<std::string, std::string> &cookies);
		AHTTPResponse& setCookie(const std::string& name, const std::string& value);
		AHTTPResponse& setCookie(const std::string& name, int value);
		
		AHTTPResponse& setBody(const std::string& body);
		bool isCGI()const;
		AHTTPResponse& setisCGI(bool isCGI);
		
		int getStatusCode() const;
		std::string &erase(ssize_t size);

		int getSoKeepaliveTime() const;
		int getSoKeepaliveIntvl() const;
		AHTTPResponse& setSoKeepaliveTime(int sokeepalive_time);
		AHTTPResponse& setSoKeepaliveIntvl(int sokeepalive_intvl);
		AHTTPResponse& decrementCountMaxKeepAlive();


};