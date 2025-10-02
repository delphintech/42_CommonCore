/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtherParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:37:07 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/07 10:01:05 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseFormData/OtherParser.hpp"

bool OtherParser::handleOtherParserFormData(Request& req, Response& res) {
	std::string content_type = req.getHeader("Content-Type");
	std::string ext = Utils::getExtension(content_type);

	//open the file and write the body string
	std::ifstream file(std::string(req.getRequestTempFilePath("body_" )).c_str(), std::ios::binary);
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

	std::string filename = "";

	if (req.getMethod() == "POST")
	{
		std::string upload_dir = req.getUploadDir();
		if (!body.empty()) {
			filename = upload_dir + "tmp_" + Utils::createRandomFileName() + ext;
			saveFile(body, filename);
		}
		res.setError(201);
	}
	else if (req.getMethod() == "PUT")
	{
		std::cerr << "PUT" << std::endl;
		std::cerr << RED << "filename: " << filename << std::endl;
		std::cerr << (Utils::System::isDirectory(req.getResolvedPath())? GREEN:RED )<< "ISDIRECTORY " << RESET << std::endl;
		std::cerr << (Utils::System::isFile(req.getResolvedPath())? GREEN:RED )<< "ISFILE " << RESET << std::endl;


		if (!Utils::System::isDirectory(req.getResolvedPath()) && !Utils::System::isFile(req.getResolvedPath()))
		{
			if (!body.empty()) {
				filename = req.getResolvedPath();
				saveFile(body, filename);
				res.setError(201);
				return (false);
			}
		}
		else  if (!Utils::System::isDirectory(req.getResolvedPath()) && Utils::System::isFile(req.getResolvedPath()))
		{
			if (!body.empty()) {
				filename = req.getResolvedPath();
				saveFile(body, filename);
				return (true);
			}
		}

		res.setError(405);//Forbidden
	}
	return (false);
}

bool OtherParser::saveFile(const std::string& content, const std::string& filename) {
	std::ofstream file(filename.c_str(), std::ios::binary);
	if (!file) {
		std::cerr << "Erreur : impossible de créer le fichier " << filename << std::endl;
		return false;
	}
	file.write(content.c_str(), content.size());
	file.close();
	return true;
}