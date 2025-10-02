/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:28:42 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/05 15:02:29 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "../webserv.h"

class Location
{
private:
    std::string					_uri;
    std::string					_root;
	std::string					_index;
	bool						_auto_index; // directory listing
	std::vector<std::string>	_methods;
	std::string					_return; // redirection
	std::string					_alias;
	std::string					_cgi_path;
	std::string					_cgi_ext;
	std::map<std::string, std::string>	_cgiInterpreters; // map of cgi interpreters; _cgiInterpreters[".php"] = "/usr/bin/php-cgi";
	std::string					_nullString;
	std::string					_upload_store;
	int							_client_max_body_size;
    
public:
    Location();
	Location(std::fstream& conf_file, std::string uris, std::string	root);
	~Location();
	Location &operator=(const Location &arg);
	Location(const Location &arg);

	void			display();
	bool			match(const std::string &uri) const;
	const std::string		&getRoot() const;
	const std::string		&getIndex() const;
	const std::string		&getUri() const;
	bool					getAutoIndex() const;
	const std::vector<std::string>	&getMethods() const;
	const std::string		&getCgiPaths() const;
	const std::string		&getCgiExts() const;
	const std::string		&getAlias() const;
	
	std::map<std::string, std::string>	&getCgiInterpreters();
	void setCgiInterpreters(std::string cgi_ext, std::string cgi_path);
	std::string &getCgiPath(std::string ext);

	void setUploadDir(std::string uploadDir);
	const std::string &getUploadDir() const;
	int getClientMaxBodySize() const;
	std::string &getReturn();
};

#endif