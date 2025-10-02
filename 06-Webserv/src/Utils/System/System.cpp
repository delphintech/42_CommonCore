/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   System.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:13:04 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/02 17:13:44 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/Utils.hpp"
#include <sys/stat.h>//for stat
#include <unistd.h>//for access
#include <limits.h>
#include <stdexcept>

/**
 * @brief get the absolute path of the executable
 * @return the path of the executable
 */
std::string Utils::System::getExecutablePath() {
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	if (count != -1) {
		std::string path(result, count);
		return path;
	} else {
		throw std::runtime_error("Unable to determine executable path");
	}
}

/**
 * @brief get the directory of the executable
 * @return the directory of the executable
 */
std::string Utils::System::getExecutableDir() {
	std::string executablePath = Utils::System::getExecutablePath();
	size_t lastSlashPos = executablePath.find_last_of('/');
	if (lastSlashPos != std::string::npos) {
		return executablePath.substr(0, lastSlashPos);
	} else {
		throw std::runtime_error("Unable to determine executable directory");
	}
}

/**
 * @brief get the type of the path
 * @param path the path to check
 * @return FILE if the path is a file
 * @return DIRECTORY if the path is a directory
 */
PathType Utils::System::resolvePathType(const std::string& path) {
	struct stat info;
	if (stat(path.c_str(), &info) == 0) {
		if (S_ISREG(info.st_mode)) {
			return P_FILE;
		} else if (S_ISDIR(info.st_mode)) {
			return P_DIRECTORY;
		}
	}
	return P_NOT_FOUND;
}

#include <fstream>
/**
 * @brief check if the file has read permission
 * @param path the path to check
 * @return true if the file has read permission, false otherwise
 */
bool Utils::System::hasReadPermission(const std::string& path) {
	if (access(path.c_str(), R_OK) == 0) {
		return true;
	} else {
		perror("access (hasReadPermission)");
		return false;
	}
}

/**
 * @brief check if the file has execute permission
 * @param path the path to check
 * @return true if the file has execute permission, false otherwise
 */
bool Utils::System::hasExecutePermission(const std::string& path) {
	if (access(path.c_str(), X_OK) == 0) {
		return true;
	} else {
		perror("access (hasExecutePermission)");
		return false;
	}
}

/**
 * @brief debug function
 * @brief get the type of the path
 * @param path the path to check
 */
std::string Utils::System::pathtypeToString(PathType pathType) {
	switch (pathType) {
		case P_FILE:
			return "FILE";
		case P_DIRECTORY:
			return "DIRECTORY";
		case P_NOT_FOUND:
			return "NOT_FOUND";
		case P_CGI:
			return "CGI";
	}
	return "UNKNOWN";
}

/**
 * @brief check if the path is a directory
 * @param path the path to check
 * @return true if the path is a directory, false otherwise
 */
bool Utils::System::isDirectory(const std::string& path) {
	return resolvePathType(path) == P_DIRECTORY;
}
bool Utils::System::isFile(const std::string& path) {
	return resolvePathType(path) == P_FILE;
}
/**
 * @brief create a directory
 * @param path the path of the directory to create
 * @return true if the directory was created, false otherwise
 */
bool Utils::System::createDirectory(const std::string& path) {
	if (mkdir(path.c_str(), 0777) == 0) {
		return true;
	} else {
		perror("mkdir");
		return false;
	}
}