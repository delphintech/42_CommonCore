/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyRequestMiddleware.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:10:53 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 13:48:01 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef nullptr
#define nullptr NULL
#endif

#include <map>
#include <vector>
#include <algorithm>
#include "middleware/AMiddleware.hpp"

class BodyRequestMiddleware : public AMiddleware {
	//private:
	//	bool extractChunkedBody(Request& req, const std::string& inputFilePath, const std::string& outputFilePath);
	public:
		bool handle(Request* req, Response* res, const DomainConfig *Dmnconfig = NULL, Client *client = NULL);
};