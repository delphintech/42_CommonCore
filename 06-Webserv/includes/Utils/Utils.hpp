/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:28:52 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/07 14:07:12 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <sys/time.h>//for gettimeofday
#include <vector>
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define PURPLE "\033[1;35m"
#define ORANGE "\033[38;5;214m"
//#define ORANGE "\033[38;2;255;165;0m" //This is the RGB value for orange
#define DIM "\033[2m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define DARKRED "\033[31m"
#define DARKGREEN "\033[32m"
#define DARKBLUE "\033[34m"
#define DARKYELLOW "\033[33m"
#define DARKCYAN "\033[36m"
#define DARKPURPLE "\033[35m"
#define DARKORANGE "\033[33m"
#define RESET "\033[0m"

enum PathType { P_FILE, P_DIRECTORY, P_CGI, P_NOT_FOUND };
class Utils{
	public:
		static int notif(std::string msg);
		static std::string normalizeHeaderName(const std::string &name);
		static std::string getMimeType(std::string& extension);
		static std::string getExtension(const std::string& Mime);
		static std::string skipWhitesSpaces(const std::string &str);
		static long getCurrentTimeInMilliseconds();
		static std::string createRandomFileName(void);
		static std::string createUUID(void);
		class System{
			public:
				static std::string getExecutableDir();
				static std::string getExecutablePath();
				static PathType resolvePathType(const std::string& path) ;
				static bool hasReadPermission(const std::string& path);
				static bool hasExecutePermission(const std::string& path);
				static std::string pathtypeToString(PathType pathType);
				static bool isDirectory(const std::string& path);
				static bool isFile(const std::string& path);
				static bool createDirectory(const std::string& path);
		};
		class Path{
			public:
				static std::string normalizePath(const std::string& path);
				static std::string normaliseDoubleSlashPath(const std::string &path);
		};
		class String
		{
			public:
				static void							trim(std::string &str, char *set);
				static std::string					get_between(std::string &str, std::string prev, std::string next);
				static std::vector<std::string>		str_to_vect(std::string str, char delimiter);
				static int							str_to_int(std::string str);
				static std::string					intToString(int nb);
				static std::string					toUpper(std::string str);
				static std::string					urlDecode(const std::string &encoded);
		};
};
