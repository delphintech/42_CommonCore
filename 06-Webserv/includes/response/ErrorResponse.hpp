/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorErrorResponse.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:49:16 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/06 12:20:26 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include "handler/ErrorHandler.hpp"
#ifndef nullptr
# define nullptr NULL
#endif

class Response;
class ErrorResponse : virtual public ErrorHandler{
	protected:
		std::string _error_message;
		bool _isError;
		int _errorCode;
	public:
		ErrorResponse(Response &res);
		ErrorResponse(const ErrorResponse& other);
		ErrorResponse& operator=(const ErrorResponse& other);
		virtual ~ErrorResponse();
		bool isError() const;
		int getErrorCode() const;
		ErrorResponse& setError(int is_error);
		const std::string &getErrormessage() const;
		ErrorResponse & createErrorResponse();
		ErrorResponse & mergeErrorPages(const DomainConfig& _domain_config);
};