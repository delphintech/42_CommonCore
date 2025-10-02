/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:07:56 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/18 15:29:44 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef nullptr
# define nullptr NULL
#endif
#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>//for open

/**
 * @brief File class
 * @Usage 
 * 	File FileClass = File(std::string("filename.txt"));
	std::string contentStr = FileClass.getContent();

	FileClass.appendToFile("content to append");
	FileClass.writeToFile("content to write");
 */
class File
{
	private:
		int _fd;
		std::string _nullString;
		std::string _path;
		File &setPath(std::string path);
	public:
		File();
		File(std::string path);
		File &operator=(const File &file);
		~File();
		std::string getContent();
		std::string getContent(const std::streampos &offsetStart, ssize_t offsetEnd);
		const std::string &getPath() const;
		int getFd()const;
		File &setFd(int fd);
		bool openFile();
		bool openWriteFile();
		bool openAppendFile();
		bool closeFile();
		bool appendToFile(const std::string &content);
		bool writeToFile(const std::string &content);
		ssize_t getSize();
		std::string readStream( size_t maxSize = 1024 * 1024);

};
