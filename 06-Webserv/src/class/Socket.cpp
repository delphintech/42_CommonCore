
#include "class/Socket.hpp"
#include <fcntl.h>//fcntl
#include <iostream>
#include <cstdlib>//exit
#include <netdb.h> // Pour gethostbyname
#include <cstring> // Pour memcpy
#include <netinet/tcp.h> // Pour TCP_NODELAY

Socket::Socket() : _sfd(-1) {
}

Socket::Socket(const Socket *src) {
	this->_sfd = src->_sfd;
	this->_address = src->_address;
}

Socket *Socket::clone() const {
	return new Socket(*this);
}

Socket::Socket(int port, const std::string& host, DomainConfig domain_configs) : domain_configs(domain_configs) {
	struct protoent		*proto;     // protocol structure a utiliser
    //struct sockaddr_in	sin;        // Describes an IPv4 Internet domain socket address
    
    // On recupere les information concernant le protocole voulu
    proto =  getprotobyname("tcp");
    if (!proto){
		Utils::notif("Proto failed");
		throw std::runtime_error("Failed to get protocol by name");
	}
    // On ouvre la socket de communication
    this->_sfd = socket(PF_INET, SOCK_STREAM, proto->p_proto); //
	
	if (_sfd == -1) {
		Utils::notif("Socket creation failed");
		throw std::runtime_error("Failed to create socket");
	}
	int opt = 1;

	// Permet de relancer le serveur immédiatement
	if (setsockopt(_sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		throw std::runtime_error("Failed to set SO_REUSEADDR");
		exit(EXIT_FAILURE);
	}

	// Permet le partage du port (uniquement si nécessaire)
	if (setsockopt(_sfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
		throw std::runtime_error("Failed to set SO_REUSEPORT");
		exit(EXIT_FAILURE);
	}

	// Désactive le buffering TCP (utile pour les protocoles interactifs)
	int flag = 1;
	if (setsockopt(_sfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) < 0) {
		throw std::runtime_error("Failed to set TCP_NODELAY");
		exit(EXIT_FAILURE);
	}
/* 	
	// Options du socket
	int opt = 1;
	if (setsockopt(_sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		throw std::runtime_error("Failed to set socket options");
	exit(EXIT_FAILURE);
	}
 */
	this->domain_configs = domain_configs;
	//Mode non-bloquant
	fcntl(_sfd, F_SETFL, O_NONBLOCK);

    // Résoudre le nom d'hôte en adresse IP
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Utiliser AF_INET pour IPv4
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host.c_str(), nullptr, &hints, &res);// getaddrinfo: convertit le nom d'hôte et le nom de service en une liste d'adresses de socket
    if (status != 0) {
   		freeaddrinfo(res);
        throw std::runtime_error("Failed to resolve hostname: " + std::string(gai_strerror(status)));
    }

    // Copier l'adresse IP résolue
    struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
    _address.sin_family = AF_INET;// precise IPv4 Internet protocols
    _address.sin_port = htons(port);// Port (listen)
    _address.sin_addr = ipv4->sin_addr;// adresse IP (host)

    freeaddrinfo(res);
}

Socket::~Socket() {
	std::cerr << "Socket closed" << std::endl;
	if (_sfd >= 0) {
		close(_sfd);
	}
}

void Socket::bindSocket() {
	// Associer le socket à une adresse et un port
	if (bind(_sfd, (struct sockaddr*)&_address, sizeof(_address)) < 0) {
		std::cerr << "bind failed" << std::endl;
		Utils::notif("Bind failed");
		throw std::runtime_error("Failed to bind socket");
	}
}

void Socket::listenSocket(int backlog) {
	if (listen(_sfd, backlog) < 0) {
		std::cerr << "listen failed" << std::endl;			
		throw std::runtime_error("Failed to listen on socket");
	}
}

int Socket::acceptConnection() {
	int new_socket = accept(_sfd, nullptr, nullptr);
	if (new_socket < 0) {
		throw std::runtime_error("Failed to accept connection");
	}
	return new_socket;
}

int Socket::getSocketFd() {
	return _sfd;
}

struct sockaddr_in Socket::getAddress() {
	return _address;
}
