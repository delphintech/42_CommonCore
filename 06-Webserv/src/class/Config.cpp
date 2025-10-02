/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:14:41 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/11 18:13:26 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/class/Config.hpp"
#include "../includes/class/Server.hpp"

Config::Config() {};

Config::Config(int ac, char** av) {
	std::fstream			conf_file;
	std::string				line;
	int						i = 1;
	_backlog = 1024;
	_so_keepalive_time = 30000;
	_so_keepalive_intvl = 100;
	_rcvbuf = 819200;
	_sndbuf = 302573;
	 _tmp_dir = "/tmp/webserv/";	
	_send_timeout = 30;
	
	// ----- Ouverture du fichier config -----
    if (ac == 1)
        conf_file.open("./conf.d/default.conf", std::ofstream::in);
    else if (ac == 2)
        conf_file.open(av[1], std::ofstream::in);
    else
	{
		Utils::notif("Too many arguments");
		throw std::invalid_argument("Too many arguments");
	}
	if (!conf_file.is_open())
	{
		Utils::notif("Bad arguments");
		throw std::invalid_argument("No such file or directory");
	}

	// ----- lecture et creation des DomainConfigs -----
	while (std::getline(conf_file, line))
	{
		if (line.find("http") != std::string::npos && line.find("{") != std::string::npos)
		{
			while (std::getline(conf_file, line))
			{
				if (line.find("#") != std::string::npos)
					continue;
				Utils::String::trim(line, (char *)"\t\n\r\v\f ;");
				size_t pos = line.find("=");
				std::string key = line.substr(0, pos);
				std::string value = line.substr(pos + 1);
				if (key == "backlog")
					_backlog = Utils::String::str_to_int(value);
				if (key == "so_keepalive")
				{
					_so_keepalive_time = Utils::String::str_to_int(value.substr(0, value.find(":")));
					_so_keepalive_intvl = Utils::String::str_to_int(value.substr(value.find(":") + 1));
				}
				if (key == "rcvbuf")
					_rcvbuf = Utils::String::str_to_int(value);
				if (key == "sndbuf")
					_sndbuf = Utils::String::str_to_int(value);
				if (key == "tmp_dir")
					_tmp_dir = value;
				if (key == "send_timeout")
					_send_timeout = Utils::String::str_to_int(value);
				if (line.find("}") != std::string::npos)
					break;
			}
		}
		if (line.find("server") != std::string::npos && line.find("{") != std::string::npos)
			this->_domains[i++] = DomainConfig(conf_file).setSendTimeout(_send_timeout);

	}
	conf_file.close();
}

Config::~Config() {
	_domains.clear();
}

Config::Config(const Config &arg) {
	_domains = arg._domains;
	_backlog = arg._backlog;
	_so_keepalive_time = arg._so_keepalive_time;
	_so_keepalive_intvl = arg._so_keepalive_intvl;
	_rcvbuf = arg._rcvbuf;
	_sndbuf = arg._sndbuf;
	_tmp_dir = arg._tmp_dir;
	_send_timeout = arg._send_timeout;
}

Config &Config::operator=(const Config &arg) {
	if (this == &arg) {
		return *this;
	}
	_domains = arg._domains;
	_backlog = arg._backlog;
	_so_keepalive_time = arg._so_keepalive_time;
	_so_keepalive_intvl = arg._so_keepalive_intvl;
	_rcvbuf = arg._rcvbuf;
	_sndbuf = arg._sndbuf;
	_tmp_dir = arg._tmp_dir;
	_send_timeout = arg._send_timeout;
	return *this;
}
void Config::display() {
	std::map<int, DomainConfig>::iterator	it;

	it = this->_domains.begin();
	while (it != this->_domains.end())
	{
		std::cout << "Domain " << it->first << " :" << std::endl;
		it->second.display();
		it++;
	}
}

const std::map<int, DomainConfig>&		Config::getDomains() const { return (this->_domains); }


size_t	Config::getBacklog() const { return (this->_backlog); }
size_t	Config::getSoKeepaliveTime() const { return (this->_so_keepalive_time); }
size_t	Config::getSoKeepaliveIntvl() const { return (this->_so_keepalive_intvl); }
size_t	Config::getRcvbuf() const { return (this->_rcvbuf); }
size_t	Config::getSndbuf() const { return (this->_sndbuf); }
std::string Config::getTmpDir() const { return _tmp_dir; }
void	Config::setTmpDir(std::string tmp_dir) { _tmp_dir = tmp_dir; }

/**
 * @brief CGI send timeout
 */
size_t	Config::getSendTimeout() const { return _send_timeout; }
void Config::setSendTimeout(size_t send_timeout) { _send_timeout = send_timeout; }