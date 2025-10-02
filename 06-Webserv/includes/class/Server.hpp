/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:55:21 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/02 07:30:20 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# ifndef nullptr
#  define nullptr NULL
# endif
#include "../webserv.h"
#include "Location.hpp"
#include "DomainConfig.hpp"
#include "Socket.hpp"
#include "PollManager.hpp"
#include <csignal>

class Server
{
	private:
		Config			_config;
		PollManager _pollManager;
		std::map<int, Client*> _clients;
		static int gSignalStatus;

	public:
		Server();
		Server(Config &config);
		// Server(const Server &arg);
		~Server();

		void	display();
		bool	start();
		void	stop();
		void	run();
		// int		Send(int sfd, std::string msg);
		static void signalHandler(int signal);
};

#endif