/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:25:08 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/16 14:23:17 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <vector>
#include "class/DomainConfig.hpp"
#ifndef nullptr
# define nullptr NULL
#endif
class Response;
class ErrorHandler
{
	public:
		struct ErrorPage {
			int status_code_int;
			std::string status_code;
			std::string error_message;
			std::string error_message_expected;
		};
		static const ErrorPage error_pages_value[];
		
	protected:
		Response &_res;
		std::map<int, std::string> _errorPagesPath;//a rename uri
		std::string _error_Pages_Path; //a rename
		std::map<int,std::pair<std::string,std::string> > _errorPagesDefault;
	public:
		ErrorHandler(Response &res);
		ErrorHandler(const ErrorHandler& other);
		ErrorHandler & operator=(const ErrorHandler& other);
		virtual ~ErrorHandler();
		std::string getErrorPage(int status);
		std::string getErrorPages(int status);
		ErrorPage getErrorMessage(int error_code);
		const ErrorHandler::ErrorPage getErrorMessage(int error_code) const;

		std::string  createErrorPage(int status);
		std::string  createErrorPage(std::string& path);
		ErrorHandler & mergeErrorPages(const DomainConfig& _domain_config);
};