/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:49:16 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/05 11:35:07 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "response/AHTTPResponse.hpp"
#include "response/ErrorResponse.hpp"
#include "response/ChunkedResponse.hpp"
class Response :virtual public AHTTPResponse , virtual public ChunkedResponse, virtual public ErrorHandler, virtual public ErrorResponse{
	
	public:
		std::string toString() const;
		std::string generateHeader() const;
		std::string getBody() const;
		std::string getBody(ssize_t offsetstart,ssize_t size = 0);
		Response();
		Response(const Response& other);
		Response& operator=(const Response& other);
		virtual ~Response();
		void clear();
		Response *clone();
		int _sndbuf;
		int getSndbuf() const;
		Response& setSndbuf(int sndbuf);


};