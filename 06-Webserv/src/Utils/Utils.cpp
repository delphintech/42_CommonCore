/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:30:28 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/09 18:21:02 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/Utils.hpp"
#include "webserv.h"
#include <ctime>//time
#include <cstdlib>//rand

// Normalize the header name by converting it to Upper-Camel-Case
std::string Utils::normalizeHeaderName(const std::string &name){
	std::string normalized_name = name;

	// Convert the first letter of each word to uppercase
	bool capitalize_next = true;
	for (size_t i = 0; i < normalized_name.size(); ++i) {
		if (capitalize_next) {
			normalized_name[i] = std::toupper(normalized_name[i]);
			capitalize_next = false;
		}
		if (normalized_name[i] == '-') {
			capitalize_next = true;
		}
	}
	return normalized_name;
}


struct MimeType {
    const char* extension;
    const char* mime_type;
};

static const MimeType mime_types[] = {
	{".aac", "audio/aac"},
	{".abw", "application/x-abiword"},
	{".arc", "application/x-freearc"},
	{".avi", "video/x-msvideo"},
	{".azw", "application/vnd.amazon.ebook"},
	{".bin", "application/octet-stream"},
	{".bmp", "image/bmp"},
	{".bz", "application/x-bzip"},
	{".bz2", "application/x-bzip2"},
	{".csh", "application/x-csh"},
	{".css", "text/css"},
	{".csv", "text/csv"},
	{".doc", "application/msword"},
	{".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
	{".eot", "application/vnd.ms-fontobject"},
	{".epub", "application/epub+zip"},
	{".gz", "application/gzip"},
	{".gif", "image/gif"},
	{".htm", "text/html"},
	{".html", "text/html"},
	{".ico", "image/vnd.microsoft.icon"},
	{".ics", "text/calendar"},
	{".jar", "application/java-archive"},
	{".jpeg", "image/jpeg"},
	{".jpg", "image/jpeg"},
	{".js", "application/javascript"},
	{".json", "application/json"},
	{".jsonld", "application/ld+json"},
	{".mid", "audio/midi"},
	{".midi", "audio/midi"},
	{".mjs", "text/javascript"},
	{".mp3", "audio/mpeg"},
	{".mp4", "video/mp4"},
	{".mpeg", "video/mpeg"},
	{".mpkg", "application/vnd.apple.installer+xml"},
	{".odp", "application/vnd.oasis.opendocument.presentation"},
	{".ods", "application/vnd.oasis.opendocument.spreadsheet"},
	{".odt", "application/vnd.oasis.opendocument.text"},
	{".oga", "audio/ogg"},
	{".ogv", "video/ogg"},
	{".ogx", "application/ogg"},
	{".opus", "audio/opus"},
	{".otf", "font/otf"},
	{".png", "image/png"},
	{".pdf", "application/pdf"},
	//{".php", "application/x-httpd-php"},
	{".php", "text/html"},
	{".ppt", "application/vnd.ms-powerpoint"},
	{".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
	{".rar", "application/vnd.rar"},
	{".rtf", "application/rtf"},
	{".sh", "application/x-sh"},
	{".svg", "image/svg+xml"},
	{".swf", "application/x-shockwave-flash"},
	{".tar", "application/x-tar"},
	{".tif", "image/tiff"},
	{".tiff", "image/tiff"},
	{".ts", "video/mp2t"},
	{".ttf", "font/ttf"},
	{".txt", "text/plain"},
	{".vsd", "application/vnd.visio"},
	{".wav", "audio/wav"},
	{".weba", "audio/webm"},
	{".webm", "video/webm"},
	{".webp", "image/webp"},
	{".woff", "font/woff"},
	{".woff2", "font/woff2"},
	{".xhtml", "application/xhtml+xml"},
	{".xls", "application/vnd.ms-excel"},
	{".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
	{".xml", "text/xml"},
	{".xpm", "image/x-xpixmap"},
	{".xul", "application/vnd.mozilla.xul+xml"},
	{".zip", "application/zip"},
	{".3gp", "video/3gpp"},
	{".3g2", "video/3gpp2"},
	{".7z", "application/x-7z-compressed"}
};

static const size_t mime_types_count = sizeof(mime_types) / sizeof(MimeType);

std::string Utils::getMimeType(std::string& extension) {
	if (extension.empty()) {
		return "text/plain"; // Type MIME par défaut
	}
	if (extension.size() == 1 ||extension[extension.size() - 1] == '/' || extension.find(".") == std::string::npos) {
		return "text/html"; // Type MIME par défaut
	}
	std::string ext = extension.substr(extension.find_last_of('.'));
	for (size_t i = 0; i < mime_types_count; ++i) {
		if (ext == mime_types[i].extension) {
			return mime_types[i].mime_type;
		}
	}
	return "application/octet-stream"; // Type MIME par défaut
}

int Utils::notif(std::string msg) {
    std::cout << COLOR(90) << msg;
    if (errno)
        std::cout << ": " << std::strerror(errno);
    std::cout << COLOR(0) << std::endl;
    return (errno);
}

std::string Utils::skipWhitesSpaces(const std::string &str) {
	size_t start = 0;
	size_t end = str.size();
	while (start < end && std::isspace(str[start])) {
		++start;
	}
	while (end > start && std::isspace(str[end - 1])) {
		--end;
	}
	return str.substr(start, end - start);
}

long Utils::getCurrentTimeInMilliseconds() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

std::string Utils::createRandomFileName(void) {
	// Générer un nom de fichier aléatoire
	std::string filename = "upload_";
	for (int i = 0; i < 8; ++i) {
		filename += "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[rand() % 62];
	}
	//timestamp
	time_t now = time(0);
	tm *ltm = localtime(&now);
    // Formater la nouvelle date dans une chaîne
    char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H-%M-%S", ltm);
	filename += buffer;
	//add extension
	filename += ".tmp";
    return filename;
}

std::string Utils::createUUID(void) {
	// Générer un nom de fichier aléatoire
	std::string UUID = "tmp_upload_";
	for (int i = 0; i < 8; ++i) {
		UUID += "0123456789ABCDEF"[rand() % 16];
		UUID += "0123456789ABCDEF"[rand() % 16];
		UUID += "0123456789ABCDEF"[rand() % 16];
		UUID += "0123456789ABCDEF"[rand() % 16];
		UUID += "-";
	}
	//timestamp
	time_t now = time(0);
	tm *ltm = localtime(&now);
	// Formater la nouvelle date dans une chaîne
	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H-%M-%S", ltm);
	UUID += "-";
	UUID += buffer;
	return UUID;
}

std::string Utils::getExtension(const std::string& Mime) {
	for (size_t i = 0; i < mime_types_count; ++i) {
		if (Mime == mime_types[i].mime_type) {
			return mime_types[i].extension;
		}
	}
	return "";
}