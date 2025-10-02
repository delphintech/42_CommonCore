/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:13:07 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/11 17:58:45 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "webserv.h"
#include "DomainConfig.hpp"

class Config
{
private:
	std::map<int, DomainConfig>	_domains;
	size_t	_backlog;
	size_t	_so_keepalive_time;
	size_t	_so_keepalive_intvl;
	size_t	_rcvbuf;
	size_t	_sndbuf;
	size_t	_send_timeout;
	std::string _tmp_dir;
	
public:
	Config();
	Config(int ac, char** av);
	~Config();

	Config(const Config &arg);
	Config &operator=(const Config &arg);

	const std::map<int, DomainConfig>&	getDomains() const;
	void								display();

	size_t	getBacklog() const;
	size_t	getSoKeepaliveTime() const;
	size_t	getSoKeepaliveIntvl() const;
	size_t	getRcvbuf() const;
	size_t	getSndbuf() const;
	std::string getTmpDir() const;
	void	setTmpDir(std::string tmp_dir);

	size_t	getSendTimeout() const;
	void setSendTimeout(size_t send_timeout);
};
