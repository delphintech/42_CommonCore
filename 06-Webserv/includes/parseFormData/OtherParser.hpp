/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtherParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:37:07 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/02 15:59:08 by nbrigui          ###   ########.fr       */
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
class OtherParser {
	public:
		static bool handleOtherParserFormData(Request& req, Response& res);

	private:
		static bool saveFile(const std::string& content, const std::string& filename) ;
	};
