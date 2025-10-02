/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:49:02 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/19 13:36:13 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response/Response.hpp"
#include <iostream>
#include "handler/ErrorHandler.hpp"
#include <map>

const ErrorHandler::ErrorPage ErrorHandler::error_pages_value[] = {
	{200, "200", "OK", "The request has succeeded."},
	{201, "201", "Created", "The request has been fulfilled and resulted in a new resource being created."},
	{202, "202", "Accepted", "The request has been accepted for processing, but the processing has not been completed."},
	{204, "204", "No Content", "The server successfully processed the request and is not returning any content."},
	{301, "301", "Moved Permanently", "The requested page has been permanently moved to a new location."},
	{302, "302", "Found", "The requested page has been temporarily moved to a new location."},
	{303, "303", "See Other", "The requested page can be found under a different URI."},
	{304, "304", "Not Modified", "The requested page has not been modified since the last request."},
	{307, "307", "Temporary Redirect", "The requested page has been temporarily moved to a new location."},
	{308, "308", "Permanent Redirect", "The requested page has been permanently moved to a new location."},
	
	{400, "400", "Bad Request", "The server could not understand your request."},
	{401, "401", "Unauthorized", "You are not authorized to view this page."},
	{402, "402", "Payment Required", "Payment is required to access this page."},
	{403, "403", "Forbidden", "You don't have permission to access this page."},
	{404, "404", "Not Found", "The page you are looking for could not be found."},
	{405, "405", "Method Not Allowed", "The method is not allowed for the requested URL."},
	{408, "408", "Request Timeout", "The server timed out waiting for the request."},
	{413, "413", "Request Entity Too Large", "The request is larger than the server is willing or able to process."},
	{415, "415", "Unsupported Media Type", "The server does not support the media type of the requested data."},
	{418, "418", "I'm a teapot", "The server refuses the attempt to brew coffee with a teapot."},
	{429, "429", "Too Many Requests", "Too many requests have been sent in a given amount of time."},
	{500, "500", "Internal Server Error", "The server has encountered a situation it doesn't know how to handle."},
	{501, "501", "Not Implemented", "The server does not support the functionality required to fulfill the request."},
	{502, "502", "Bad Gateway", "The server, while acting as a gateway or proxy, received an invalid response from the upstream server it accessed in attempting to fulfill the request."},
	{503, "503", "Service Unavailable", "The server is not ready to handle the request."},
	{504, "504", "Gateway Timeout", "The server, while acting as a gateway or proxy, did not receive a timely response from the upstream server specified by the URI."},
	{505, "505", "HTTP Version Not Supported", "The server does not support the HTTP protocol version used in the request."}
};

std::string ErrorHandler::createErrorPage(std::string& path) {
	std::string error_page = "";
	std::ifstream file(path.c_str());
	std::cerr << "Opened file: " << path << std::endl;
	if (!file.is_open()) {
			std::cerr << "Error: could not open file " << path << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

static const size_t error_pages_value_count = sizeof(ErrorHandler::error_pages_value) / sizeof(ErrorHandler::ErrorPage);

ErrorHandler::ErrorPage ErrorHandler::getErrorMessage(int error_code) {
	ErrorPage error_pages_value_found = {0, "0", "unknown", "unknown"};
	for (size_t i = 0; i < error_pages_value_count; ++i) {
		if (error_code == error_pages_value[i].status_code_int) {
			error_pages_value_found = error_pages_value[i];
			break;
		}
	}
	return error_pages_value_found;
}
const ErrorHandler::ErrorPage ErrorHandler::getErrorMessage(int error_code) const{
	ErrorPage error_pages_value_found = {0, "0", "unknown", "unknown"};
	for (size_t i = 0; i < error_pages_value_count; ++i) {
		if (error_code == error_pages_value[i].status_code_int) {
			error_pages_value_found = error_pages_value[i];
			break;
		}
	}
	return error_pages_value_found;
}

std::string ErrorHandler::createErrorPage(int status) {
	std::cerr <<"ErrorHandler::createErrorPage: generator: " <<__FILE__ <<":"<< __LINE__ << std::endl;

ErrorPage error_pages_value_found = {0, "0", "unknown", "unknown"};
	for (size_t i = 0; i < error_pages_value_count; ++i) {
        if (status == error_pages_value[i].status_code_int) {
			error_pages_value_found = error_pages_value[i];
            break;
        }
    }

	
	int status_code = error_pages_value_found.status_code_int;
	std::string error_message = error_pages_value_found.error_message;
	std::string error_message_expected = error_pages_value_found.error_message_expected;

	std::stringstream ss;
	ss << "<!DOCTYPE html>";
	ss << "<html lang=en>";
	ss << "	<head>";
	ss << "	<meta charset=UTF-8>";
	ss << "		<meta name=viewport content=\"width=device-width, initial-scale=1.0\">";
	ss << "		<title>"<< status_code << " " << error_message << "</title>";
	ss << "		<!-- Server Error page Generated -->";    
	ss << "		<style>";
	ss << "			body {";
	ss << "				background-color: #f8f8f8;";
	ss << "				color: #333;";
	ss << "				font-family: Arial, sans-serif;";
	ss << "				text-align: center;";
	ss << "				padding: 50px;";
	ss << "			}";
	ss << "			h1 {";
	ss << "				font-size: 50px;";
	ss << "				margin-bottom: 20px;";
	ss << "			}";
	ss << "			p {";
	ss << "				font-size: 20px;";
	ss << "				margin-bottom: 30px;";
	ss << "			}";
	ss << "			a {";
	ss << "				color: #007BFF;";
	ss << "				text-decoration: none;";
	ss << "				font-size: 18px;";
	ss << "			 }";
	ss << "			a:hover {";
	ss << "				text-decoration: underline;";
	ss << "			}";
	ss << "		</style>";
	ss << "	</head>";
	ss << "	<body>";
	ss << "		<h1>"<< status_code <<"</h1>";
	ss << "		<p>" << error_message << ". " << error_message_expected << "</p>";
	ss << "		<p><a href=\"/\">Go back to the homepage</a></p>";
	ss << "	</body>";
	ss << "</html>";
	//std::cout << "ErrorHandler::createErrorPage: generator: \n" << ss.str() << std::endl;
	return ss.str();
}

ErrorHandler::ErrorHandler(Response &res): _res(res) , _errorPagesPath() , _error_Pages_Path(), _errorPagesDefault() {
	
}

ErrorHandler::ErrorHandler(const ErrorHandler& other): _res(other._res), _errorPagesPath(other._errorPagesPath), _error_Pages_Path(other._error_Pages_Path), _errorPagesDefault(other._errorPagesDefault) {
}

ErrorHandler & ErrorHandler::operator=(const ErrorHandler& other) {
	if (this == &other) {
		return *this;
	}
 	_res = other._res;
	_errorPagesPath = other._errorPagesPath;
	_error_Pages_Path = other._error_Pages_Path;
	_errorPagesDefault = other._errorPagesDefault;


	return *this;
}

ErrorHandler::~ErrorHandler() {
}

std::string ErrorHandler::getErrorPages(int status) {
	std::map<int, std::string>::iterator it = _errorPagesPath.find(status);
	if (it != _errorPagesPath.end()) {
		return it->second;
	}
	return "";
}


std::string resolveRootPath(const std::string &root, const std::string &thissystempath);
	//resolve the error pages path
std::string ErrorHandler::getErrorPage(int status) {
	std::string error_page = "";

	//0 - merge error pages
	//_res.mergeErrorPages();
	
	//1 - specific location error page
 	std::string path = _error_Pages_Path; //_res.getErrorPages(status);//a rename
	if (path != "") {
/* 
		std::string thissystempath = Utils::System::getExecutableDir() + "/";
		path = resolveRootPath(path, thissystempath);
		path = Utils::Path::normaliseDoubleSlashPath(path); */
		std::string error_page = this->createErrorPage(path);
		if (error_page != "") {
			_res.setVersion()
			.setStatusCode(status)
			.setStatusMessage(getErrorMessage(status).error_message)
			.setHeader("Content-Length", error_page.size())
			.setHeader("Content-Type", "text/html")
			.setBody(error_page);
			return error_page;
		}
	}

 	//2  - default error page generated
	error_page = this->createErrorPage(status);
	if (error_page != "") {
			_res.setVersion()
			.setStatusCode(status)
			.setStatusMessage(getErrorMessage(status).error_message)
			.setHeader("Content-Length", error_page.size())
			.setHeader("Content-Type", "text/html")
			.setBody(error_page);

		return error_page;
	}
	//4 - default 404 error page
	error_page = this->createErrorPage(404);
			_res.setVersion()
			.setStatusCode(status)
			.setStatusMessage(getErrorMessage(status).error_message)
			.setHeader("Content-Length", error_page.size())
			.setHeader("Content-Type", "text/html")
			.setBody(error_page);
	return error_page;
}
std::string resolveLocationRootPath(const std::string &locationRoot, const std::string &serverRoot, const std::string &thissystempath);
ErrorHandler & ErrorHandler::mergeErrorPages(const DomainConfig& domain_config) {
	_errorPagesPath = domain_config.getError_page();
	std::string _error_Pages_uri = getErrorPages(_res.getErrorCode());

	_error_Pages_Path = "";
	//si on suit nginx, error_pages de location a priorité sur error_pages de server
	//de plus error_pages est une liste de code d'erreur et d'uri

	std::string resolvedPath = "";
	std::string resolvedRootPath = "";

	std::string thissystempath = Utils::System::getExecutableDir() + "/";
	resolvedRootPath = resolveRootPath(domain_config.getRoot(), thissystempath);
	resolvedPath = resolvedRootPath;
	

	Location locations;
	locations = domain_config.getLocation(_error_Pages_uri/* "/error_pages/404.html" */);

	resolvedPath = resolveLocationRootPath(locations.getRoot(), resolvedRootPath, thissystempath);

	resolvedPath += _error_Pages_uri /* "/error_pages/404.html" */;
	resolvedPath = Utils::Path::normaliseDoubleSlashPath(resolvedPath);
	// Priorité aux error_pages de DomainConfig
	_error_Pages_Path = resolvedPath;

	return *this;
} 