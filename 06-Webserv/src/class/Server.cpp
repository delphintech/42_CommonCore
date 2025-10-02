/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:34:28 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/02 07:31:14 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Server.hpp"
#include "class/Socket.hpp"
#include "class/Config.hpp"
#include <csignal>

Server::Server() : _config(Config()) {}

// ----- Create the server according to the config file -----
Server::Server(Config &config) : _config(config), _pollManager(&_config){}

void	Server::display() { this->_config.display(); };

void Server::signalHandler(int signal) {
	gSignalStatus = signal;
}

int Server::gSignalStatus = 0;

void Server::run() {
	std::signal(SIGINT, Server::signalHandler);
	std::signal(SIGQUIT, Server::signalHandler);
	Utils::notif("Server on");
	srand(time(nullptr));
	while (true) {
		_pollManager.pollConnections();
	//	_pollManager.handleTimeouts();
		if (gSignalStatus != 0) {			
			Utils::notif("Signal received, stopping server");
			Utils::notif(gSignalStatus == SIGINT ? "SIGINT" : 
				gSignalStatus == SIGQUIT ? "SIGQUIT" : "Unknown signal");
			break;
		}
	}
}
bool	Server::start() {
	return (true);
}

void	Server::stop() { /* close(this->_sfd); */ }

Server::~Server() {}
