/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPChunkedRequest.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:35:04 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/12 16:13:09 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>//std::stringstream

class AHTTPChunkedRequest{
	protected:
		std::streampos _offsetStart;
		std::streampos _offsetEnd;
		bool _isParsed;
		bool _isComplete;
		bool _isChunked;
	public:
		AHTTPChunkedRequest();
		virtual ~AHTTPChunkedRequest();
		AHTTPChunkedRequest(const AHTTPChunkedRequest &other);
		AHTTPChunkedRequest& operator=(const AHTTPChunkedRequest& other);
		AHTTPChunkedRequest* operator=(AHTTPChunkedRequest* other);
		const std::streampos &getOffsetStart() const;
		const std::streampos &getOffsetEnd() const;
		void setOffsetStart(std::streampos offsetStart);
		void setOffsetEnd(std::streampos offsetEnd);
		bool isParsed() const;
		void setIsParsed(bool isParsed);
		bool isComplete() const;
		void setComplete(bool isComplete);
		bool isChunked() const;
		void setChunked(bool isChunked);

};