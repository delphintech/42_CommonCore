/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:07:56 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/05 15:34:23 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/File.hpp"
#include <sys/stat.h>
#include <cerrno>

File::File():_fd(-1){};
File::File(std::string path):_fd(-1){
	this->setPath(path);
};
File::~File(){
	this->closeFile();
};

File &File::operator=(const File &file){
	this->setPath(file.getPath());
	this->setFd(file.getFd());
	return *this;
};
std::string File::getContent(){
	this->closeFile();
	this->openFile();
	std::string contentToString;
	char buffer[4096 + 1];
	int ret;
	lseek(_fd, 0, SEEK_SET);
	while ((ret = read(_fd, buffer, 4096)) != 0) {
		if (ret == -1) {
			std::cerr << "Failed to read file" << std::endl;
			this->closeFile();
			return _nullString;
		}
		buffer[ret] = '\0';
		contentToString.insert(contentToString.length(), buffer, ret);
	}
	this->closeFile();
	return contentToString;
};
#include <cstring>
std::string File::getContent(const std::streampos &offsetStart, ssize_t size = 0){
	this->closeFile();
	this->openFile();
	std::string contentToString;
	char buffer[4096 + 1] = {0};
	ssize_t ret;
	ssize_t totalRead = 0;
	// Positionner la tête de lecture
	if (lseek(_fd, offsetStart, SEEK_SET) == (off_t)-1) {
		std::cerr << "Failed to seek to position: " << offsetStart  << std::endl;
		closeFile();
		return "";
	}
	while ((ret = read(_fd, buffer, 4096)) != 0) {
		if (ret == -1) {
			std::cerr << "Failed to read file" << std::endl;
			this->closeFile();
			return _nullString;
		}
		buffer[ret] = '\0';
		contentToString.insert(contentToString.length(), buffer, ret);
		totalRead += ret;
		if (size != 0 && totalRead >= size) {
			contentToString.erase(size/* contentToString.length() - (totalRead - size )*/);	
			break;
		}
	}
	this->closeFile();
	return contentToString;
};

File &File::setPath(std::string path){
	_path = path;
	return *this;
};
const std::string &File::getPath() const {
	return _path;
};
int  File::getFd() const {
	return _fd;
};
File & File::setFd(int fd){
	_fd = fd;
	return *this;
};

/**
 * Opens a file in read-only mode
 */
bool  File::openFile(){
	this->closeFile();
	_fd = open(_path.c_str(), O_RDONLY);
	if (_fd == -1) {
		std::cerr << "Failed to open file: " << _path << std::endl;
		return false;
	}
	return true;
};

/**
 * Opens a file in write-only mode
 */
bool  File::openWriteFile(){
	this->closeFile();
	_fd = open(_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (_fd == -1) {
		std::cerr << "Failed to open file: " << _path << std::endl;
		return false;
	}
	return true;
};

/**
 * Opens a file in append mode
 */
bool  File::openAppendFile(){
	this->closeFile();
	_fd = open(_path.c_str(),  O_CREAT | O_RDWR | O_APPEND, 0644);
	if (_fd == -1) {
		std::cerr << "Failed to open file: " << _path << std::endl;
		return false;
	}
	return true;
};
bool  File::closeFile(){
	if (_fd < 0) {
		return true;
	}
	close(_fd);
	_fd = -1;
	return true;
};

bool  File::appendToFile(const std::string &content){
	this->closeFile();
	this->openAppendFile();
	if (_fd == -1) {
		return false;
	}
	if (write(_fd, content.c_str(), content.size()) == -1) {
		std::cerr << "Failed to write to file: " << _path << std::endl;
		this->closeFile();
		return false;
	}
	this->closeFile();
	return true;
};


bool File::writeToFile(const std::string &content){
	this->closeFile();
	this->openWriteFile();
	if (_fd == -1) {
		return false;
	}
	if (write(_fd, content.c_str(), content.size()) == -1) {
		std::cerr << "Failed to write to file: " << _path << std::endl;
		this->closeFile();
		return false;
	}
	this->closeFile();
	return true;
};

//use stat to get the file size
ssize_t File::getSize(){
	struct stat fileStat;
	if (stat(_path.c_str(), &fileStat) == -1) {
		std::cerr << "Failed to get file size: " << strerror(errno) << std::endl;
		return -1;
	}
	return fileStat.st_size;
};
