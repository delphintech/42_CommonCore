/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:34:02 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/12 14:08:47 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../webserv.h"
#include "DomainConfig.hpp"
#include "request/Request.hpp"
#include "response/Response.hpp"

class Client
{
private:
	int					_fd;

	Client(const Client &client);	// copy operator desactivé
	Client &operator=(const Client &client);	// operator assignement desactivé

	bool _is_closed;
	DomainConfig *_config;
	Request *_request;
	Response *_response;
	std::string _ip;
	
public:
	std::multimap<std::string, DomainConfig> *_server_configs;
	Client();
	Client(int fd, DomainConfig *config);
	Client(int fd, DomainConfig *config, std::multimap<std::string, DomainConfig> *server_configs);
	~Client();

	void	disconnect();
	void setIsclose();
	int		msg() const;
	bool	isClosed() const;
	int		getFd() const;
	const DomainConfig &getDomainConfig() const;
	//void setDomainConfig(DomainConfig *config);
	const DomainConfig *getDomainConfigPtr() const;
	const DomainConfig &getDomainConfig(std::string hostname) const;
	void setUpDomainConfig(std::string hostname);
	const std::multimap<std::string, DomainConfig> *getDomainConfigs() const;
	Request *getRequest();
	Response *getResponse();
	Request *setRequest(Request *request);
	Response *setResponse(Response *response);
	void setIp(std::string ip);
	std::string getIp();
};

#endif