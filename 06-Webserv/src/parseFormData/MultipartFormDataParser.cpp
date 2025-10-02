/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultipartFormDataParser.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:00:29 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/07 09:57:25 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parseFormData/MultipartFormDataParser.hpp"

bool MultipartFormDataParser::handleMultipartFormData(Request& req, Response& res) {
	std::string content_type = req.getHeader("Content-Type");
	std::string boundary = 	content_type.substr(content_type.find("boundary=") + 9);
	if (boundary.empty()) {
		std::cerr << "Boundary not found in Content-Type" << std::endl;
		res.setError(400); // Bad Request
		return false;
	}

	//open the file and write the body string
	std::ifstream file(std::string(req.getRequestTempFilePath("body_")).c_str(), std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open temporary file" << std::endl;
		res.setError(500);
		return false;
	}
	std::string body;
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        body.append(buffer, file.gcount());
    }
    body.append(buffer, file.gcount()); // Ajout des derniers octets lus
    file.close();
	std::vector<std::string> parts = splitMultipartBody(body, boundary); 

	std::vector<std::string>::iterator ite = parts.end();
	for (std::vector<std::string>::iterator it = parts.begin(); it != ite; ++it) {
		std::string headers, content;
		parseMultipartPart(*it, headers, content);

		std::string name = extractHeaderValue(headers, "name");
		std::string filename = extractHeaderValue(headers, "filename");
		std::string content_type = extractHeaderValueContentType(headers);

		std::string upload_dir = req.getUploadDir();
		if (!filename.empty()) {
			filename = upload_dir + Utils::createUUID() + filename;
			saveFile(content, filename);
			req.addFormData(name, req.getUploadDir(), content_type, filename);
		} else {
			req.addFormData(name, content, content_type, "");
		}
	}
	req.setIsMultipart(true);
	res.setError(201);//created
	return false;
}


// Fonction pour extraire les en-têtes et le contenu de chaque partie
void MultipartFormDataParser::parseMultipartPart(const std::string& part, std::string& headers, std::string& content) {
	size_t header_end = part.find("\r\n\r\n");
	if (header_end != std::string::npos) {
		headers = part.substr(0, header_end);
		content = part.substr(header_end + 4);
	}
};
std::string MultipartFormDataParser::extractHeaderValue(const std::string& headers, const std::string& key) {
	size_t pos = headers.find(key + "=\"");
	if (pos != std::string::npos) {
		size_t start = pos + key.size() + 2;
		size_t end = headers.find("\"", start);
		if (end != std::string::npos) {
			return headers.substr(start, end - start);
		}
	}
	return "";
}

std::string MultipartFormDataParser::extractHeaderValueContentType(const std::string& headers) {
	size_t pos = headers.find("Content-Type: ");
	if (pos != std::string::npos) {
		return headers.substr(pos + 14);
	}
	return "";
}

bool MultipartFormDataParser::saveFile(const std::string& content, const std::string& filename) {
	std::ofstream file(filename.c_str(), std::ios::binary);
	if (!file) {
		std::cerr << "Erreur : impossible de créer le fichier " << filename << std::endl;
		return false;
	}
	file.write(content.c_str(), content.size());
	file.close();
	return true;
}
std::vector<std::string> MultipartFormDataParser::splitMultipartBody(const std::string& body, const std::string& boundary) {
	std::vector<std::string> parts;
	std::string delimiter = "--" + boundary;
	size_t start = 0, end;
	while ((end = body.find(delimiter, start)) != std::string::npos) {
		std::string part = body.substr(start, end - start);
		if (!part.empty()) {
			parts.push_back(part);
		}
		start = end + delimiter.size() + 2; // Skip \r\n
	}
	return parts;
}