
#pragma once
#include <vector>
#include <poll.h>
#include "Socket.hpp"
#include "DomainConfig.hpp"
#include "Config.hpp"
#include <map>
#include <vector>
#include "request/Request.hpp"
#include "response/Response.hpp"

class Client;
/**
 * PollManager class
 * poll() wrapper
 * Manages the sockets and the connections
 * Handles the new connections and the client requests
 * Handles the timeouts
 */
class PollManager
{
	public:
		PollManager();
		PollManager(const Config& _config);
		PollManager(const Config* _config);
		~PollManager();
		
		void initializeServerSockets();		
		void addSocket(int fd);
		void removeSocket(int fd);
		void removeClient(int client_fd);
		int wait(int timeout);
		int getSocketAt(int index) const;
		void pollConnections();
		void handleNewConnection(int server_fd);
		void handleClientRequest(int client_fd);
		bool handleCleanClientConnection(int client_fd) ;
		void handleClientChunkedRequest(int client_fd);
		bool handleClientResponse(int client_fd);
		void handleClientReset(int client_fd);
		void handleTimeouts() ;
		bool handleTimeouts(int client_fd) ;
		bool isServerSocket(int fd);

		bool isValidFd(int fd);
		void setPollout(int fd);
		void unSetPollout(int fd);
		void setPollError(int fd);
		void resesetRevent(int fd);
		pollfd* getFds(int fd);
		pollfd getFd(int fd);
		bool isPollEvent(int fd,short event);

	private:
		const Config* _config; // Pointeur vers la configuration
		std::vector<pollfd> _fds;
		std::vector<Socket*> _sockets;
		std::map<int, DomainConfig> server_configs;//server_fd, domain_config
		std::multimap<std::string, DomainConfig> server_configs_multimap;//server_fd, domain_config
		std::map<int, Client*> _clients;
		time_t _last_check;

};