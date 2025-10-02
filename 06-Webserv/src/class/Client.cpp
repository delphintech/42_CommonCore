/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:54:54 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/12 14:57:14 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Client.hpp"
#include "Utils/Utils.hpp"


Client::Client():_fd(), _is_closed(false), _config() {

}

Client::Client(const Client &client){
	_fd = client._fd;
	_is_closed = client._is_closed;
	_config = client._config;
	_server_configs = client._server_configs;
	_request = client._request->clone();
	_response = client._response->clone();
	_ip = client._ip;
}

Client &Client::operator=(const Client &client) {
	if (this == &client) {
		return *this;
	}
	_fd = client._fd;
	_is_closed = client._is_closed;
	_config = client._config;
	_server_configs = client._server_configs;
	_request = client._request;
	_response = client._response;
	_ip = client._ip;
	return *this;
}

Client::Client(int fd, DomainConfig *config) : _fd(fd), _is_closed(false), _config(config) {
	long int time = Utils::getCurrentTimeInMilliseconds();
	_request = new Request();
	_request->setLastActive(time);
	_response = new Response();
	_ip = "";
}

Client::Client(int fd, DomainConfig *config, std::multimap<std::string, DomainConfig> *server_configs) : _fd(fd), _is_closed(false), _config(config), _server_configs(server_configs) {
	long int time = Utils::getCurrentTimeInMilliseconds();
	_request = new Request();
	_request->setLastActive(time);
	_response = new Response();
	_ip = "";
}

Client::~Client() {
	if (_request != NULL)
		delete _request;
	_request = NULL;
	if (_response != NULL)
		delete _response;
	_response = NULL;
	if (_server_configs != NULL)
		delete _server_configs;
}

void	Client::disconnect() {
	if (this->_fd > 0)
		close(this->_fd);
	_is_closed = true;
}

void Client::setIsclose() {
	_is_closed = true;
}

int		Client::msg() const {
	int		nb_read = 1;
	char	buf[1024];
	
	nb_read = read(this->_fd, buf, 1023);
	buf[nb_read] = '\0';
	if (nb_read > 0)
		std::cout << buf << std::endl;
	return (nb_read);
}

bool	Client::isClosed() const {
	return _is_closed;
}

int		Client::getFd() const { return _fd;
}

const DomainConfig &Client::getDomainConfig() const { return *_config;
}
const DomainConfig *Client::getDomainConfigPtr() const { return _config;
}

/* void Client::setDomainConfig(DomainConfig *config) {
	_config = config;
} */
const DomainConfig &Client::getDomainConfig(std::string hostname) const {
	std::multimap<std::string, DomainConfig>::const_iterator it = _server_configs->begin();
	while (it != _server_configs->end() && hostname != "") {
		if (it->second.getServer_name().size() != 0)
		{
			std::vector<std::string> server_name = it->second.getServer_name();
			for (size_t i = 0; i < server_name.size(); i++)
			{
				if (server_name[i] == hostname)
				{
					return it->second;
				}
			}
		}		
		it++;
	}
	
	it = _server_configs->begin();
	return it->second;
}

void Client::setUpDomainConfig(std::string hostname) {
	for (std::multimap<std::string, DomainConfig>::iterator it = _server_configs->begin(); it != _server_configs->end(); ++it) {
		std::vector<std::string> server_name = it->second.getServer_name();
		for (size_t i = 0; i < server_name.size(); i++) {
			if (server_name[i] == hostname) {
				std::cerr<< GREEN << "DomainConfig found for hostname: " << hostname << RESET <<std::endl;
				_config = &it->second;
				return ;
			}
		}
	}
	std::ostringstream host_port_oss;
	host_port_oss << _config->getHost().first << ":" << _config->getListen();
	_config = &_server_configs->find(host_port_oss.str())->second;	
	return;
}
const std::multimap<std::string, DomainConfig> *Client::getDomainConfigs() const {
	return _server_configs;
}
Request *Client::getRequest() { return _request;
}

Request *Client::setRequest(Request *request) {
	int rcvbuf = 8192;
	bool is_timeout = false;
	int timeout_value = 30000;
	time_t lastActive = Utils::getCurrentTimeInMilliseconds();
	if (_request != NULL){
		rcvbuf = _request->getRcvbuf();
		is_timeout = _request->getIsTimeout();
		timeout_value = _request->getTimeoutValue();
		lastActive = _request->getLastActive();
		delete _request;
	}
	_request = request;
	_request->setRcvbuf(rcvbuf);
	_request->setIsTimeout(is_timeout);
	_request->setTimeoutValue(timeout_value);
	_request->setLastActive(lastActive);
	return _request;
}

Response *Client::getResponse() { return _response;
}

Response *Client::setResponse(Response *response) {
	int sndbuf = 4096;
	int sokeepalive_time = 100;
	int sokeepalive_intvl = 10;
	if (_response != NULL)
	{
		sndbuf = _response->getSndbuf();
		sokeepalive_time = _response->getSoKeepaliveTime();
		sokeepalive_intvl = _response->getSoKeepaliveIntvl();
		delete _response;
	}
	_response = response;
	_response->setSndbuf(sndbuf);
	_response->setSoKeepaliveTime(sokeepalive_time);
	_response->setSoKeepaliveIntvl(sokeepalive_intvl);
	return _response;
}

void Client::setIp(std::string ip) {
	_ip = ip;
}

std::string Client::getIp() {
	return _ip;
}