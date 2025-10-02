/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMultipartRequest.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:37:07 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/02 12:07:06 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef nullptr
#define nullptr NULL
#endif
#include <map>
#include <string>
/*parsedChunkedRequest*/
class AMultipartRequest
{
	public:
		struct FormData {
			std::string name;
			std::string data;
			std::string content_type;
			std::string filename;
		};
	protected:

		std::map<std::string,FormData > _form_data;
		std::string _boundary;
		bool _isMultipart;
	public:
		virtual ~AMultipartRequest();
		AMultipartRequest& operator=(const AMultipartRequest& other);
		AMultipartRequest *operator=(AMultipartRequest* other);

		AMultipartRequest& setFormData(const std::string& name, const FormData& data);
		std::map<std::string,FormData > getFormDatas() const;

		AMultipartRequest& setFormDatas(const std::map<std::string,FormData >& form_data);
		AMultipartRequest& addFormData(const std::string& name, const FormData& data);
		AMultipartRequest& addFormData(const std::string& name, std::string data, std::string content_type, std::string filename);
		
		AMultipartRequest& clearFormData();
		FormData getFormData(const std::string& name) const;

		AMultipartRequest& setBoundary(const std::string& boundary);
		std::string getBoundary() const;

		AMultipartRequest& setIsMultipart(bool isMultipart);
		bool isMultipart() const;


};