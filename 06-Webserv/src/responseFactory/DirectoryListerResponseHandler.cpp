/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListerResponseHandler.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:36:08 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/06 14:37:41 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "responseFactory/DirectoryListerResponseHandler.hpp"
#include "request/Request.hpp"

DirectoryListerResponseHandler::DirectoryListerResponseHandler(const std::string &requestPath,const std::string& file_path, Request *req)
	:_req(req), _file_path(file_path),_requestPath(requestPath), _isError(false) {

};

void DirectoryListerResponseHandler::generateHeaders(Response *res) {
	if (this->getIsError()) {
		res->setError(this->getErrorCode());
		return;
	}
	res->setVersion().setStatusCode(this->getStatusCode())
	.setHeader("Content-Length", _body.size())
	.setHeader("Content-Type","text/html; charset=UTF-8")
	.setKeepAlive(_req->getHeader("Connection") != "close");
	_req->getMethod() == "HEAD" ? res->setBody("") : res->setBody(_body);
	
} 

std::string DirectoryListerResponseHandler::getBody() {
	this->_body = executeDirectoryLister();
	std::cerr << " [debug] DirectoryListerResponseHandler::getBody() "<< __FILE__ <<":"<< __LINE__ << std::endl;
	return _body;
}

std::string DirectoryListerResponseHandler::executeDirectoryLister() {
	std::cout << PURPLE <<"[debug] DirectoryListerResponseHandler::executeDirectoryLister() " << RESET << __FILE__ <<":"<<__LINE__ << std::endl;

	std::ostringstream html;
	html << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
	html << "<meta charset=\"UTF-8\">\n<title>Index of " << _file_path << "</title>\n";
	html << "<style>\n";
	html << "body { font-family: Arial, sans-serif; padding: 20px; }\n";
	html << "h1 { font-size: 24px; }\n";
	html << "h2 { font-size: 20px; }\n";
	html << "table { width: 100%; border-collapse: collapse; }\n";
	html << "th, td { padding: 8px; text-align: left; border-bottom: 1px solid #ddd; }\n";
	html << "a { text-decoration: none; color: #007BFF; }\n";
	html << "a:hover { text-decoration: underline; }\n";
	html << "</style>\n";
	html << "</head>\n<body>\n";
	html << "<h1>Index of " << _file_path << "</h1>\n";
	html << "<h2>Index of " << _requestPath << "</h2>\n";
	html << "<table>\n";
	html << "<tr><th>Name</th><th>Size</th><th>Last Modified</th><th>Action</th></tr>\n";

	DIR* dir = opendir(_file_path.c_str());
	std::cerr << " [debug] DirectoryListerResponseHandler::executeDirectoryLister() "<< __FILE__ <<":"<< __LINE__ << " _file_path: " << _file_path << std::endl;
	if (dir == nullptr) {
		std::cerr << " [ERROR] DirectoryListerResponseHandler::executeDirectoryLister() "<< __FILE__ <<":"<< __LINE__ << " Unable to open directory" << std::endl;
		html << "<tr><td colspan=\"4\">Unable to open directory</td></tr>\n";
	} else {
		struct dirent* entry;
		while ((entry = readdir(dir)) != nullptr) {

			std::string name = entry->d_name;
			if (name == "." || name == "..")
				continue;

			std::string fullPath = _file_path + "/" + name;
			struct stat fileStat;
			if (stat(fullPath.c_str(), &fileStat) == -1) {
				continue;
			}

			html << "<tr>";
			std::string filename = Utils::Path::normaliseDoubleSlashPath( _requestPath + "/" + name);
			html << "<td><a href=\"" << filename << "\">" << name  <<"</a></td>";
			html << "<td>" << fileStat.st_size << "</td>";
			html << "<td>" << ctime(&fileStat.st_mtime) << "</td>";
			// Ajout du bouton Delete
			if (_req->isAllowedMethodDelete())
				html << "<td><button onclick=\"deleteFile('" << filename << "')\">Delete</button></td>";
			else
				html << "<td></td>";
			html << "</tr>\n";
		}
		closedir(dir);
	}
	// Ajouter le script JavaScript pour envoyer la requête DELETE
	html << "<script>\n";
	html << "function deleteFile(fileName) {\n";
	html << "    if (confirm('Are you sure you want to delete ' + fileName + '?')) {\n";
	html << "        fetch(fileName, {\n";
	html << "            method: 'DELETE',\n";
	html << "            headers: {\n";
	html << "                'Content-Type': 'application/json'\n";
	html << "            },\n";
	html << "        })\n";
	html << "        .then(response => {\n";
	html << "            if (response.ok) {\n";
	html << "                alert('File deleted successfully!');\n";
	html << "                location.reload();\n";
	html << "            } else {\n";
	html << "                alert('Failed to delete the file.');\n";
	html << "            }\n";
	html << "        })\n";
	html << "        .catch(error => {\n";
	html << "            alert('Error: ' + error);\n";
	html << "        });\n";
	html << "    }\n";
	html << "}\n";
	html << "</script>\n";	
	html << "</table>\n";
	html << "</body>\n</html>\n";
	if (_req->getMethod() == "GET" || _req->getMethod() == "HEAD")
		this->setStatusCode(200);
	std::cerr << " [debug] DirectoryListerResponseHandler::executeDirectoryLister() "<< __FILE__ <<":"<< __LINE__ << std::endl;
	return html.str();
}
