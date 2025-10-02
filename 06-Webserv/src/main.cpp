/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:57:34 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/29 09:45:20 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.h"
#include "../includes/class/Server.hpp"
#include "../includes/class/Client.hpp"
#include "../includes/class/Config.hpp"

int main(int ac, char **av) {
	// ----- Parsing du fichier config -----
	Config	config = Config(ac, av);

	// ----- lecture et creation des Servers -----
	Server server = Server(config);

	// ----- Print DomainConfig -----
	server.display();

	std::signal(SIGINT, SIG_IGN);
	std::signal(SIGQUIT, SIG_IGN);

	// ----- Lancement des serveurs -----
	server.run();

	return (EXIT_SUCCESS);
}
