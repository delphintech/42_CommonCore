/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyRequestMiddleware.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:11:36 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:50:32 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "middleware/BodyRequestMiddleware.hpp"
#include <unistd.h>//read
#include "Utils/Utils.hpp"
#include <sys/stat.h>
#include "class/File.hpp"

bool extractChunkedBody(Request* req, const std::string& inputFilePath, const std::string& outputFilePath) {
	std::ifstream inputFile(inputFilePath.c_str(), std::ios::binary);
	inputFile.seekg(req->getHeaderSize());
	if (!inputFile.is_open()) {
		std::cerr << "Failed to open input file: " << inputFilePath << std::endl;
		return false;
	}
	std::ofstream outputFile(outputFilePath.c_str(), std::ios::binary);
	if (!outputFile.is_open()) {
		std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
		inputFile.close();
		return false;
	}

	std::string line;
	size_t chunkSize;
	char buffer[4096] = {0};

	while (true) {
		std::getline(inputFile, line);
		if (line.empty()) {
			inputFile.close();
			outputFile.close();
			return false;
		}

		// Convert chunk size from hex to decimal
		chunkSize = std::strtoul(line.c_str(), nullptr, 16);
		if (chunkSize == 0) {
			// End of chunks
			break;
		}
		// Read the chunk data
		size_t totalBytesRead = 0;
		while (totalBytesRead < chunkSize) {
			memset(buffer, 0, sizeof(buffer));
			size_t bytesToRead = std::min(sizeof(buffer), chunkSize - totalBytesRead);
			inputFile.read(buffer, bytesToRead);
			size_t bytesRead = inputFile.gcount();
			if (bytesRead <= 0) {
				inputFile.close();
				outputFile.close();
				return false;
			}
			outputFile.write(buffer, bytesRead);
			totalBytesRead += bytesRead;
		}

		// Read "\r\n" after the chunk data
		memset(buffer, 0, sizeof(buffer));
		inputFile.read(buffer, 2);
		if (inputFile.gcount() != 2 || buffer[0] != '\r' || buffer[1] != '\n') {
			inputFile.close();
			outputFile.close();
			return false;
		}
	}
	inputFile.close();
	outputFile.close();

	File file(outputFilePath);
	req->setBodySize( file.getSize());
	return true;
}

bool extractBody(Request* req, const std::string& inputFilePath, const std::string& outputFilePath) {
	std::ifstream inputFile(inputFilePath.c_str(), std::ios::binary);
	inputFile.seekg(req->getHeaderSize());
	if (!inputFile.is_open()) {
		std::cerr << "Failed to open input file: " << inputFilePath << std::endl;
		return false;
	}
	std::ofstream outputFile(outputFilePath.c_str(), std::ios::binary);
	if (!outputFile.is_open()) {
		std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
		inputFile.close();
		return false;
	}

	std::string line;
	char buffer[4096] = {0};
		// Read the chunk data
	size_t bytesRead = 1;
	size_t totalBytesRead = 0;
	while (bytesRead > 0) {
		memset(buffer, 0, sizeof(buffer));
		size_t bytesToRead =sizeof(buffer);
		inputFile.read(buffer, bytesToRead);
		bytesRead = inputFile.gcount();
		if (bytesRead == 0) {
			break;
		}
		outputFile.write(buffer, bytesRead);
		totalBytesRead += bytesRead;
	}
	(void)totalBytesRead;
	inputFile.close();
	outputFile.close();

	File file(outputFilePath);
	req->setBodySize( file.getSize());
	return true;
}

void checkRequestBody(Request* req)
{
	File file(req->getRequestTempFilePath());
	ssize_t ssize = file.getSize() != -1 ? file.getSize() : 0;
	std::streampos offsetStart = ssize - 6;
	//get 5last bytes
	std::string lastFileContent = file.getContent(offsetStart, 6);
	if ( req->getHeader("Transfer-Encoding") == "chunked" && lastFileContent.find("0\r\n\r\n") != std::string::npos) {
		req->setComplete(true);
		if (extractChunkedBody(req, req->getRequestTempFilePath(), req->getRequestTempFilePath("body_"))) {
			req->setIsParsed(true);
			req->setChunked(false);
			req->setComplete(true);
		}
		return;
	}
	else if (req->getHeader("Transfer-Encoding") == "" && req->getHeaderSize() + std::atoi(req->getHeader("Content-Length").c_str()) <= req->getRequestTempFilesize() ) {
		req->setIsParsed(true);
		req->setChunked(false);
		req->setComplete(true);
		extractBody(req, req->getRequestTempFilePath(), req->getRequestTempFilePath("body_"));
		return;
	}
	else {
		if (req->isComplete())
			return;
		req->setIsParsed(false);
		req->setChunked(false);
		req->setComplete(false);
	}
}

bool BodyRequestMiddleware::handle(Request* req, Response* res, const DomainConfig *Dmnconfig, Client *client) {
	(void)Dmnconfig;
	(void)client;
	checkRequestBody(req);
	if (!req->isComplete()) {
	std::ifstream temp_file_size(req->getRequestTempFilePath().c_str(), std::ios::binary | std::ios::ate);
		if (!temp_file_size) {
			std::cerr << "Failed to open temporary file for reading" << std::endl;
			res->setError(500);
			std::cout << ORANGE <<"[debug] END BodyRequestMiddleware::handle " << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
			return false;
		}
		req->setRequestTempFilesize(temp_file_size.tellg());
		
		checkRequestBody(req);
		temp_file_size.close();

		if (req->isComplete()) {
			req->clearRequestRaw();
			return true;
		}
		return false;
	}
	req->clearRequestRaw();
	return true;
}