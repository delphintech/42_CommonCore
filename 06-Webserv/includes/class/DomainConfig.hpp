#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Location.hpp"
#include <set>

class DomainConfig
{
	protected:
		int								_sfd;    	// fd de la socket de communication
		int								_listen;
		std::pair<std::string, long>	_host;
		std::vector<std::string>		_server_name;
		//std::pair<int,std::string>		_error_page;
		std::map<int,std::string>		_error_page;
		int								_client_max_body_size;
		std::string						_root;
		std::string						_index;
		std::vector<Location>   		_locations;
		std::map<std::string, std::string>	_addHeaders;
		std::set<std::string, std::greater<std::string> >  _sorted_paths;
		Location _nullLocation;
		size_t _send_timeout;
	public:
		DomainConfig();
		DomainConfig(std::fstream &conf_file); // Cree le serveur selon le fichier config
		DomainConfig& operator=(const DomainConfig &arg); // assignment operator desactivé
		DomainConfig& operator=(const DomainConfig *arg); // assignment operator desactivé
		DomainConfig(const DomainConfig &arg);
		DomainConfig(const DomainConfig *arg);
		~DomainConfig();

	// ---------- GETTERS ----------
		int								getFd();
		int								getListen() const;
		std::pair<std::string, long>	getHost() const;
		std::vector<std::string>		getServer_name() const;
		std::map<int,std::string>		getError_page() const;
		int								getClient_max_body_size() const;
		std::string						getRoot() const;
		std::string						getIndex() const;
		std::vector<Location>   		getLocations() const;

		// ---------- SETTERS ----------
		void 	setHost(std::string ip);
		// Server&	set_fd(int sfd);
		void	display();
		DomainConfig &getDomainConfig();
		DomainConfig *clone();
		const std::map<std::string, std::string> &getAddHeaders()const;
		void setAddHeaders(std::string key, std::string value);

		void createSetLocation();
		const Location &getLocation(const std::string &uri) const;
		const Location &getLocation(const std::string &uri, const std::string &method) const;

		const Location &getNullLocation() const { return _nullLocation; };

		void setErrorPage(int key, std::string value);
		const std::map<int,std::string> &getErrorPages() const;
		int getClientMaxBodySize() const { return _client_max_body_size; };//return the client_max_body_size for this location

		size_t getSendTimeout() const;
		DomainConfig& setSendTimeout(size_t send_timeout);

};