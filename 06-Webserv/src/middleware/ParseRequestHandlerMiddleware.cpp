/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequestHandlerMiddleware.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:14:15 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 15:02:31 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "middleware/ParseRequestHandlerMiddleware.hpp"
#include <unistd.h>//read
#include "request/Request.hpp"
#include "Utils/Utils.hpp"
#include "class/File.hpp"

void parseRequest(Request *req, const std::string& request);
bool ParseRequestHandlerMiddleware::handle(Request* req, Response* res, const DomainConfig *Dmnconfig, Client *client) {
	(void)Dmnconfig;
	if (req->isParsed()) {
		return true;
	}
	(void)res;
	if (!req->isParsed()) {
		int rcvbuf = req->getRcvbuf();
		rcvbuf = rcvbuf > 819200 ? 819200 : rcvbuf;
		char buffer[819200];
		ssize_t bytes_read = read(req->getClientFd(), buffer, rcvbuf);
		if (bytes_read < 0) {//client closed connection error
			std::cerr << "Connection closed ----------- " <<__FILE__<<":"<<__LINE__ << std::endl;
			req->setForceClose(true);
			return false;
		}
		if (bytes_read == 0) {//client closed by sending a FIN packet
			ssize_t peek_bytes = recv(req->getClientFd(), buffer, 1, MSG_PEEK);
			if (peek_bytes == 0) {
				//std::cerr << "Client a fermé la connexion proprement." << std::endl;
				req->setForceClose(true);
			}else {
				if (req->getLastActive() + req->getTimeoutValue() < Utils::getCurrentTimeInMilliseconds()) {
					req->setIsTimeout(true);
					res->setError(408);
					std::cerr<<RED << "Timeout" << RESET<<std::endl;
					return false;
				}
			}
			req->setIsResetRevents(true);
			return false;
		}
		std::string data_str(buffer, bytes_read);
		req->setLastActive(Utils::getCurrentTimeInMilliseconds());
		req->setIsReadTimeout(false);
		//std::cerr << GREEN << "data: "<< data_str << RESET << std::endl;
		if (req->getHeaderSize() == 0 && !req->isRequestRawComplete())
			req->addToRequestRaw(data_str);

		//save the request in a file
		File file(req->getRequestTempFilePath());
		file.appendToFile(data_str);
		if (req->getHeaderSize() == 0 && !req->isRequestRawComplete()) {
			return false;
		}
		if (req->getHeaderSize() == 0) {			
			parseRequest(req, req->getRequestRaw());
			client->setUpDomainConfig(req->getHost());
		}
		req->setIsParsed(true);

		//set the size of the request
		ssize_t ssize = file.getSize() != -1 ? file.getSize() : 0;
		req->setRequestTempFilesize(ssize);
		std::streampos offsetStart = ssize - 7;
		//get 6last bytes
		std::string lastFileContent = file.getContent(offsetStart, 7);
		if ( req->getHeader("Transfer-Encoding") == "chunked" && lastFileContent.find("\n0\r\n\r\n") != std::string::npos) {
			req->setComplete(true);
		}
		else if (req->getHeader("Transfer-Encoding") == "chunked") {
			req->setChunked(true);
			req->setIsParsed(false);
			req->setComplete(false);
			return false;
		}
		return true;
	}
	return true; //next middleware
}


void parseRequest(Request *req, const std::string& request) {
	//set HeaderSize
	size_t pos_end_header = request.find("\r\n\r\n");
	if (pos_end_header != std::string::npos) {
		req->setHeaderSize( pos_end_header + 4);
	}

	req->setHeaderRaw(request.substr(0, req->getHeaderSize() - 1));
	std::istringstream iss(req->getHeaderRaw()); 
	std::string line;
	std::getline(iss, line);
	std::istringstream first_line(line);
	//rappel: first_line = "GET / HTTP/1.1"
	// istringstream consideres space as a delimiter
	std::string method, uri, protocol;
	first_line >> method >> uri >> protocol;
	uri = Utils::String::urlDecode(uri);
	req->setMethod(method).setUri(uri).setProtocol(protocol);
	req->setQueryParamsFromPath(uri);
	while (std::getline(iss, line)) {

		if (line.find("\r\n\r\n") != std::string::npos)//end of headers
			break;

		if (line.empty()) {
			break;
		}
		size_t pos = line.find(":");
		if (pos == std::string::npos) {
			continue;
		}
		std::string key = line.substr(0, pos);
		std::string value =  Utils::skipWhitesSpaces( line.substr(pos + 1));
		key = Utils::normalizeHeaderName(key);
		req->setHeader(key, value);
	}

	std::string tmp = req->getHeader("Host");
	size_t pos = tmp.find(":");
	if (pos != std::string::npos) {
		req->setHost(tmp.substr(0, pos));
		req->setPort(tmp.substr(pos + 1));
	} else {
		req->setHost(tmp);
		req->setPort("80");
	}

	std::string path = req->getUri();
	pos = path.find("?");
	if (pos != std::string::npos) {
		path = path.substr(0, pos);
		if (path.find(".") != std::string::npos) {
			if (path[path.size() - 1] == '/') {
				path = path.substr(0, path.size() - 1);
			}
		}
	}
	req->setPath(path);
	std::string queryString = req->getUri();
	pos = queryString.find("?");
	if (pos != std::string::npos) {
		queryString = queryString.substr(pos + 1);
		req->setQueryString(queryString);
	}
}