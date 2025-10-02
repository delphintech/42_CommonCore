/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultipartFormDataParser.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:04:19 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/05 17:04:21 by nbrigui          ###   ########.fr       */
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
#include <cstring>//for std::strncmp

class MultipartFormDataParser {
	public:
		static bool handleMultipartFormData(Request& req, Response& res);

	private:
		static void parseMultipartPart(const std::string& part, std::string& headers, std::string& content);
		static std::string extractHeaderValue(const std::string& headers, const std::string& key);
		static std::string extractHeaderValueContentType(const std::string& headers);
		static bool saveFile(const std::string& content, const std::string& filename) ;
		static std::vector<std::string> splitMultipartBody(const std::string& body, const std::string& boundary);
	};
