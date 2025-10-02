/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponseHandler.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:19:32 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/20 16:52:25 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

class Response;
class IResponseHandler {
	public:
		virtual ~IResponseHandler() {}
		virtual void generateHeaders(Response *res) = 0;
		virtual std::string getBody() = 0;
		virtual int getStatusCode() const = 0;
		virtual void setStatusCode(int statusCode) = 0;
		
		virtual bool getIsError() const = 0;
		virtual int getErrorCode() const = 0;
		virtual void setErrorCode(int errCode) = 0;
};