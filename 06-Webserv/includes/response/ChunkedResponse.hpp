/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:53:27 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/17 19:04:32 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>//std::stringstream

class ChunkedResponse{
	protected:
		bool _isComplete; // _isComplete = true if the response is complete
		bool _isGenerated; // _isGenerated = true if the response is generated
		bool _isChunked; // _isChunked = true if the response is chunked response
		std::string _chunkedHeader; // _chunkedHeader = chunked header
		ssize_t _chunkedHeaderSize; // _chunkedHeaderSize = size of the chunked header
		bool _isHeaderSent; // _isHeaderSent = true if the header is sent
		std::string _bodyPathFile; // _bodyPathFile = path to the file to be sent
		ssize_t _bodySize; // _bodySize = size of the body to be sent
		ssize_t _offsetstart; // offsetstart = offset to start reading the file
		ssize_t _offsetSend; // offsetSend = offset to start sending the file
		int _bufferSize; // size = size of the chunk to be sent


	public:
		ChunkedResponse();
		virtual ~ChunkedResponse();
		ChunkedResponse& operator=(const ChunkedResponse& other);
		ChunkedResponse& setChunked(bool chunked = false);
		ChunkedResponse& setChunkedHeader(const std::string& header);
		ChunkedResponse& setBodyPathFile(const std::string& bodyPathFile);
		ChunkedResponse& setOffsetStart(ssize_t offsetstart);
		ChunkedResponse& setBufferSize(int bufferSize);
		bool isComplete()const;
		bool isGenerated()const;
		bool isChunked()const;
		std::string getChunkedHeader()const;
		std::string getBodyPathFile()const;
		ssize_t getOffsetStart()const;
		int bufferSize()const;
		std::string getContent();
		std::string getContent(ssize_t offsetstart);
		std::string getContent(ssize_t offsetstart, ssize_t size);
		ssize_t getBodySize()const;
		ssize_t getChunkedHeaderSize()const;
		bool isHeaderSent()const;
		ChunkedResponse& setHeaderSent(bool isHeaderSent);
		ChunkedResponse& setBodySize(ssize_t bodySize);
		ChunkedResponse& setChunkedHeaderSize(ssize_t chunkedHeaderSize);
		ChunkedResponse& setComplete(bool isComplete);
		ChunkedResponse& setGenerated(bool isGenerated);



};