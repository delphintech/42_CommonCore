#pragma once
# define SERVER_HPP
# ifndef nullptr
#  define nullptr NULL
# endif
#include <netinet/in.h>
#include <string>
#include "DomainConfig.hpp"

class Socket {
	private:
		int _sfd;
		struct sockaddr_in _address; // Describes an IPv4 Internet domain socket address

	public:
		DomainConfig domain_configs;
		Socket();
		Socket(Socket const *src);
		Socket *clone() const;
		Socket(int port, const std::string& host, DomainConfig domain_configs);
		~Socket();

		void bindSocket();
		void listenSocket(int backlog = 42); // backlog: nombre de connexions simultanées acceptées par la socket 
		int acceptConnection();
		int getSocketFd() ;
		struct sockaddr_in getAddress();
		bool operator==(const int other_fd) const {
			return this->_sfd == other_fd;
		}
};