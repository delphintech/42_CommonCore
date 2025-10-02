/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:51:55 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/11 20:32:23 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/Utils.hpp"

/**
 * @brief normalize the path, add a slash if it's missing at the end
 * @param path the path to normalize
 * @return the normalized path
 * 
 */
std::string Utils::Path::normalizePath(const std::string& path) {
	std::string normalized_path = path;
	if (!normalized_path.empty() && normalized_path[normalized_path.size() - 1] == '/') {
		normalized_path = normalized_path.substr(0, normalized_path.size() - 1);
	}
	return normalized_path;
}

/**
 * @brief normalize the path, remove the slash if it's present at the end
 * @param path the path to normalize
 * @return the normalized path
 */
std::string Utils::Path::normaliseDoubleSlashPath(const std::string &path) {
	std::string normalised = path;
	size_t pos;
	while ((pos = normalised.find("//")) != std::string::npos) {
		normalised.replace(pos, 2, "/");
	}
	return normalised;
}