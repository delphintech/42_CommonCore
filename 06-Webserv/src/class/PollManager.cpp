/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:32:35 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/12 14:57:48 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/PollManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "class/Client.hpp"
#include "class/Config.hpp"
#include "responseFactory/StaticFileResponseHandler.hpp"
#include "response/Response.hpp"
#include "request/Request.hpp"
#include "Utils/Utils.hpp"
#include "middleware/ParseRequestHandlerMiddleware.hpp"
#include "middleware/MiddlewareChain.hpp"
#include "middleware/BodyRequestMiddleware.hpp"
#include "middleware/ContentResponseFactoryMiddleWare.hpp"
#include "middleware/HttpIsAllowedMethodMiddleware.hpp"
#include "middleware/PathResolverMiddleware.hpp"
#include <iomanip>
#include "class/File.hpp"

PollManager::PollManager() 
{
	this->_config = nullptr;
	this->initializeServerSockets();
}

PollManager::PollManager(const Config *config) : _config(config)
{
	this->initializeServerSockets();
}

PollManager::PollManager(const Config &config) : _config(&config)
{
	this->initializeServerSockets();
}

PollManager::~PollManager()
{
	std::cerr << RED << "PollManager::~PollManager() " << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
	std::cerr << RED << "PollManager::~PollManager() close socket" << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
	for (size_t i = 0; i < _sockets.size(); i++) {
		close(_sockets[i]->getSocketFd());
	}
	std::cerr << RED << "PollManager::~PollManager() delete" << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
	for (size_t i = 0; i < _sockets.size(); ++i) {		
        delete _sockets[i];
    }
	std::cerr << RED << "PollManager::~PollManager() delete Client" << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
	for(std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		it->second->~Client();
		delete it->second;
	}
	std::cerr << RED << "PollManager::~PollManager() delete Complete" << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
}

/**
** Initializes the server sockets
** Creates a new Socket object for each domain in the configuration
*/
void PollManager::initializeServerSockets() {
		std::map<int, DomainConfig>::const_iterator	it;
		
		it = this-> _config->getDomains().begin();
		// Create a new Socket object for each domain in the configuration
		while (it != this->_config->getDomains().end()) 
		{
			Socket* socket = new Socket(const_cast<DomainConfig*>(&it->second)->getListen(), const_cast<DomainConfig*>(&it->second)->getHost().first, it->second);
			socket->bindSocket();
			socket->listenSocket(_config->getBacklog());
			_sockets.push_back(socket); // Stocker le pointeur Socket dans le vecteur _sockets
			//add server socket to poll
			this->addSocket(socket->getSocketFd());
			//stocker la config du serveur dans le map server_configs
			server_configs[socket->getSocketFd()] = it->second;
			std::ostringstream host_port_oss;
   			host_port_oss << it->second.getHost().first << ":" << it->second.getListen();
			server_configs_multimap.insert(std::pair<std::string, DomainConfig>(host_port_oss.str(), &it->second));
			it++;
		}
		std::string tempDir = _config->getTmpDir();
		if (!Utils::System::isDirectory(tempDir))
			Utils::System::createDirectory(tempDir);
}

/**
** Polls the sockets for incoming connections
*/
void PollManager::addSocket(int fd)
{
	pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_fds.push_back(pfd);
}

void PollManager::resesetRevent(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++){
		if (_fds[i].fd == fd){
			_fds[i].revents = 0;
			break;
		}
	}
}
void PollManager::setPollout(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++){
		if (_fds[i].fd == fd){
			_fds[i].events |= POLLOUT;
			break;
		}
	}
}

void PollManager::unSetPollout(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++){
		if (_fds[i].fd == fd){
			_fds[i].events &= ~POLLOUT;
			break;
		}
	}
}

void PollManager::setPollError(int fd){

	for (size_t i = 0; i < _fds.size(); i++){
		if (_fds[i].fd == fd){
			_fds[i].events |= POLLERR;
			break;
		}
	}
}
/**
** Removes a socket from the poll
*/
void PollManager::removeSocket(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++){
		if (_fds[i].fd == fd){
			shutdown(fd, SHUT_RDWR);// // Désactive la lecture et l'écriture @BUG
			_fds.erase(_fds.begin() + i);
			close(fd);
			break;
		}
	}
}

void PollManager::removeClient(int client_fd)
{
	if (_clients.find(client_fd) != _clients.end()) {
		if (_clients[client_fd] != nullptr) {
			delete _clients[client_fd];
			_clients.erase(client_fd);
		}			
	}
}

int PollManager::getSocketAt(int index) const
{
	return _fds[index].fd;
}


/**
** Polls the sockets for incoming connections
** @param timeout: timeout in milliseconds
*/
int PollManager::wait(int timeout = 100)
{
	int poll_count = poll(_fds.data(), _fds.size(), timeout);
	if (poll_count < 0) {
		perror("poll error");
		//throw std::runtime_error("poll error");
		return -1;
	}
	return poll_count;
}


/**
** Checks if a file descriptor is a server socket
** @param fd: file descriptor
** @return true: if the file descriptor is a server socket
** @return false: if the file descriptor is a client socket
*/
bool PollManager::isServerSocket(int fd) {
	for (size_t i = 0; i < _sockets.size(); i++) {
		if (_sockets[i]->getSocketFd() == fd) {
			return true;
		}
	}
	return false;
}

/**
 * debug print event
 */
void printEventType(pollfd fds){
	if (fds.revents & POLLIN) {
			std::cerr << PURPLE << "Server::pollConnections() : POLLIN on fd " << fds.fd << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
		}
		if (fds.revents & POLLOUT) {
			std::cerr << PURPLE << "Server::pollConnections() : POLLOUT on fd " << fds.fd << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
		}
		if (fds.revents & POLLERR) {
			std::cerr << PURPLE << "Server::pollConnections() : POLLERR on fd " << fds.fd << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
		}
		if (fds.revents & POLLHUP) {
			std::cerr << PURPLE << "Server::pollConnections() : POLLHUP on fd " << fds.fd << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
		}
		if (fds.revents & POLLNVAL) {
			std::cerr << PURPLE << "Server::pollConnections() : POLLNVAL on fd " << fds.fd << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
		}
		if (fds.revents & POLLRDHUP) {
			std::cerr << PURPLE << "Server::pollConnections() : POLLRDHUP on fd " << fds.fd << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
		}
		if (!(fds.revents & (POLLOUT | POLLIN | POLLERR | POLLHUP | POLLNVAL | POLLRDHUP))) {
			std::cerr << PURPLE << "other event on fd " << fds.fd << " "<< fds.revents << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
			}
		std::cerr << YELLOW<<fds.fd << " is PollEvent: 0x" << std::hex << std::setw(4) << std::setfill('0') << fds.revents << std::dec << std::endl;
}

/**
** Polls the sockets for incoming connections
** Handles new connections and client requests
*/
void PollManager::pollConnections() {
	int timeout = 100;
	int poll_count = this->wait(timeout);
	bool isServerSocketfd = false;
	int events_handled = 0;
	if (poll_count == 0) {
		//std::cerr << "poll timeout" << std::endl;
		this->handleTimeouts();
		return;
    }
	if (poll_count == -1) {
		return;
	}
	
	for (size_t i = 0; i < _fds.size() && events_handled < poll_count; i++) {
		pollfd fds = _fds[i];
		if (fds.fd == -1) {
			continue;
		}
		isServerSocketfd = isServerSocket(fds.fd);
		//debug print event
		//printEventType(fds);
		if (!isServerSocketfd){ //client is closed
			if (this->handleCleanClientConnection(fds.fd)){
				i--;
				continue;
			}
		}

		if (fds.revents & (POLLERR | POLLHUP | POLLNVAL)) { //error on fd detected by poll
			events_handled++;
			std::cerr << RED << "Server::pollConnections() : POLLERR/POLLHUP/POLLNVAL on fd " << fds.fd << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
			Client *client = _clients[fds.fd];
			if (client != nullptr) {
				client->setIsclose();
			}

			if (this->handleCleanClientConnection(fds.fd)) {
				i--;
				continue;
			}
		} else if (isServerSocketfd && fds.revents & POLLIN) { //new connection from client in server socket
			events_handled++;
			handleNewConnection(fds.fd);
		} else if (!isServerSocketfd && (fds.revents &  POLLOUT)) {
			events_handled++;
			handleClientResponse(fds.fd);
		} else if (!isServerSocketfd && (fds.revents & POLLIN)) {
			events_handled++;
			handleClientRequest(fds.fd);
		}
	}
}

/**
 * get pollfd by fd
 * @param fd: file descriptor
 * @return pollfd: pollfd struct (it should be checked if the fd is valid and the pointer is not null)
 * @warning a pointer to the pollfd struct that means it can be modified
 */
pollfd* PollManager::getFds(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++){
		if (_fds[i].fd == fd){
			return &_fds[i];
		}
	}
	return nullptr;
}

bool PollManager::isPollEvent(int fd,short event){
	pollfd fds = this->getFd(fd);
	if (fds.fd == -1)
		return false;
	return fds.revents & event;
}

/*
** get pollfd by fd
** @param fd: file descriptor
** @return pollfd: pollfd struct (it should be checked if the fd is valid != -1)
** @warning: it's a copy of the pollfd struct
*/
pollfd PollManager::getFd(int fd) {
    for (size_t i = 0; i < _fds.size(); i++) {
        if (_fds[i].fd == fd) {
            pollfd pfd = _fds[i];
            return pfd;
        }
    }
	pollfd pfd ={-1, 0, 0}; 
    return pfd; // Indique que le fd n'a pas été trouvé
}

bool PollManager::isValidFd(int fd) {
	return _clients.find(fd) != _clients.end();
}

/**
** Handles new connections
** Accepts new connections and adds them to the poll
** @param server_fd: server file descriptor
*/
void PollManager::handleNewConnection(int server_fd) {
	sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int new_client_fd = accept(server_fd,(sockaddr*)&client_addr, &client_len);
	//ip address
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client_addr.sin_addr, ip, INET_ADDRSTRLEN);	
	if (new_client_fd < 0) {
		perror("handleNewConnection accept failed");
		return;
	}
	if (fcntl(new_client_fd, F_SETFL, O_NONBLOCK) < 0) {
		perror("handleNewConnection fcntl failed");
		close(new_client_fd);
		return;
	}
	this->addSocket(new_client_fd);
	DomainConfig *Dmnconfig = &this->server_configs[server_fd];

 	std::ostringstream host_port_oss;
    host_port_oss << Dmnconfig->getHost().first << ":" << Dmnconfig->getListen();
 	// Utiliser equal_range pour obtenir la plage d'éléments avec la clé host_port
	  std::multimap<std::string, DomainConfig> *result;
	  result = new std::multimap<std::string, DomainConfig>();
	for (std::multimap<std::string, DomainConfig>::iterator it = server_configs_multimap.begin(); it != server_configs_multimap.end(); ++it) {
		if (it->first == host_port_oss.str())
	  		result->insert(std::pair<std::string, DomainConfig>(host_port_oss.str(), it->second));
	}
	_clients[new_client_fd] = new Client(new_client_fd, Dmnconfig, result);
	 std::ostringstream oss;
	 oss << ip << ":" << ntohs(client_addr.sin_port);
	_clients[new_client_fd]->getRequest()->setClientFd(new_client_fd);
	_clients[new_client_fd]->getRequest()->setTimeoutValue(_config->getSoKeepaliveTime());
	_clients[new_client_fd]->getRequest()->setRcvbuf(_config->getRcvbuf());
	_clients[new_client_fd]->getResponse()->setSndbuf(_config->getSndbuf());
	_clients[new_client_fd]->getResponse()->setSoKeepaliveTime(_config->getSoKeepaliveTime());
	_clients[new_client_fd]->getResponse()->setSoKeepaliveIntvl(_config->getSoKeepaliveIntvl());
	_clients[new_client_fd]->setIp(oss.str());
	std::cerr << ORANGE << "New connection from " << ip << ":" << ntohs(client_addr.sin_port) << RESET << "--> assigned to client_fd " << new_client_fd << std::endl;
	std::cerr << ORANGE << "to server_fd " << server_fd << " ip " << server_configs[server_fd].getHost().first << ":" << server_configs[server_fd].getListen() << RESET << std::endl;
	
	//create date time
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::ostringstream ossDateTime;
	ossDateTime << "[TIME: "	
	<< 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec
	<< "] Connection accepted: " << oss.str() <<"-->  to client_fd " << new_client_fd ;
	ossDateTime <<" server_fd " << server_fd << " ip " << server_configs[server_fd].getHost().first << ":" << server_configs[server_fd].getListen() << RESET << std::endl;
	File file("logs/access.log");
	file.appendToFile(ossDateTime.str());
	//std::cerr << ORANGE <<  ossDateTime.str() << RESET << std::endl;
}

/**
** Handles client requests
** Reads the request from the client and sends a response
** @param client_fd: client file descriptor
*/
void PollManager::handleClientRequest(int client_fd) {
	Request *req = _clients[client_fd]->getRequest();
	req->setClientFd(client_fd);
	Response *res =  _clients[client_fd]->getResponse();
	const DomainConfig *Dmnconfig = &this->_clients[client_fd]->getDomainConfig();
	if (!res->isComplete() && !req->isComplete()) {
		MiddlewareChain chain(Dmnconfig, _clients[client_fd]);
		chain.addMiddleware(new ParseRequestHandlerMiddleware());//initate request, 1st time-> middleware //read and  set up req->host, req->port
		chain.addMiddleware(new BodyRequestMiddleware());//read request
		chain.addMiddleware(new PathResolverMiddleware());//resolve path
		chain.addMiddleware(new HttpIsAllowedMethodMiddleware());//check if method is allowed
		chain.addMiddleware(new ContentResponseFactoryMiddleWare());//generate response //Va etre modifie
		chain.execute(req, res);
	}
	if (req->getForceClose()) {
		Client *client = _clients[client_fd];
		if (client != nullptr) {
			client->setIsclose();
		}
		return;
	}
	if (req->getIsResetRevents() && !res->isError()) {
		this->resesetRevent(client_fd);
		req->setIsResetRevents(false);
		return;
	}
	if ((req->isComplete() || res->isComplete()))
		this->setPollout(client_fd);
	return;
}

/**
 * Handles client requests Reseting the client request/response
 *  unset pollout and set the client to close if the client has req->getHeader("Connection") == "close")
 */
void PollManager::handleClientReset(int client_fd){
	Request *req = _clients[client_fd]->getRequest();
	Response *res = _clients[client_fd]->getResponse();
	this->unSetPollout(client_fd);
	if ( _clients[client_fd]->isClosed())
		return;
	if (res->getSoKeepaliveIntvl() == 0 &&req->getHeader("Connection") == "keep-alive") {
		_clients[client_fd]->setIsclose();
		return;
	}
	if (req->getHeader("Connection") == "close") {
		_clients[client_fd]->setIsclose();
		return;
	}
	_clients[client_fd]->setResponse(new Response());
	req = _clients[client_fd]->setRequest(new Request());
}

bool PollManager::handleClientResponse(int client_fd) {
	Response *res = _clients[client_fd]->getResponse();
	Request *req = _clients[client_fd]->getRequest();
	const DomainConfig &Dmnconfig = this->_clients[client_fd]->getDomainConfig();
	std::string header = "";
	if (req->isComplete() || res->isComplete()) {
		if (res->isError()) {
			res->setKeepAlive(req->getHeader("Connection") != "close");
			res->mergeErrorPages(Dmnconfig);
			res->createErrorResponse();
		}
		if (!res->isHeaderSent()) {
			header = res->generateHeader();
			res->setComplete(true);
			res->decrementCountMaxKeepAlive();
		}
		ssize_t offsetstart = res->getOffsetStart();
		ssize_t size = res->getSndbuf();
		std::string	body = res->getBody(offsetstart, size);

		ssize_t byteSend = 0;
		//send the header first
		if (!res->isHeaderSent()) {
			std::cerr << BLUE << " from " << _clients[client_fd]->getIp() << "  on client_fd : " << client_fd << "\n"<<RESET;
			std::cerr <<  CYAN << "\t < \n" << req->getHeaderRaw() << RESET << std::endl;
			byteSend = send(client_fd, header.c_str(), header.size(), body.size() == 0? 0 : MSG_MORE);//MSG_MORE = include header in the same packet
			res->setHeaderSent(true);
			if (byteSend > 0 && static_cast<size_t>(byteSend) == header.size())
				std::cerr << DIM << GREEN << "\n \t > \n" << header << RESET  << std::endl;
			
			
		}
		//send the body	
		if (body.size() > 0){
			this->setPollout(client_fd);
			byteSend = send(client_fd, body.c_str(), body.size(), MSG_NOSIGNAL); // MSG_MORE means that the header is included in the same packet; if SIGPIPE is raised, the server will handle it. desactive SIGPIPE with MSG_NOSIGNAL
			if (byteSend < 0) {
				std::cerr << RED << "Error sending response to client " << client_fd << RESET << " " << __FILE__ <<":"<<__LINE__ << std::endl;
				_clients[client_fd]->setIsclose();
				this->handleClientReset(client_fd);
				return false;
			}else if (byteSend == 0) {
				std::cerr << RED << "Client closed connection during send to client " << client_fd << RESET << " " << __FILE__ <<":"<<__LINE__ << std::endl;
				_clients[client_fd]->setIsclose();
				this->handleClientReset(client_fd);
				return false;
			}else if (byteSend < static_cast<ssize_t> (body.size())) {
				std::cerr << RED << "Socket not ready for writing, will retry... to client " << client_fd << RESET << " " << __FILE__ <<":"<<__LINE__ << std::endl;
			}
			res->setOffsetStart(offsetstart + byteSend);
			offsetstart = res->getOffsetStart();
			body = res->getBody(offsetstart, size);
			if (body.size() == 0){
				std::cerr << GREEN << "client " << client_fd << " Complete " << RESET << std::endl;
				this->handleClientReset(client_fd);
				return false;
			}
			return true; 
		}
		this->handleClientReset(client_fd);
		return false;// no body sent, normal return
	}
	return true;
}

/**
** Handles cleaning up client connections
** Closes the connection if the client has closed it
** erases the client from the _clients map
** @param client_fd: client file descriptor
*/
bool PollManager::handleCleanClientConnection(int client_fd) {
//	std::cerr << RED << "void Server::handleCleanClientConnection start" << RESET << std::endl;
	Client *client = _clients[client_fd];
	if (client == nullptr) {
		std::cerr << "Client not found for fd: " << client_fd << std::endl;
		return true;
	}
	if (client->isClosed()) {
	//	std::cerr << RED << "void Server::handleCleanClientConnection close" << RESET << std::endl;
		//create date time
			time_t now = time(0);
			tm *ltm = localtime(&now);
			std::ostringstream ossDateTime;
			ossDateTime << "[TIME: "	
			<< 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec
			<< "] Connection Close: from " << client->getIp() <<" fd= " << client_fd << std::endl;
			File file("logs/access.log");
			file.appendToFile(ossDateTime.str());
			std::cerr << ORANGE <<  ossDateTime.str() << RESET;
		this->removeClient(client_fd);
		this->removeSocket(client_fd);
		return true;
	}
//	std::cerr << RED << "void Server::handleCleanClientConnection End" << RESET << std::endl;
	return false;
}

void PollManager::handleClientChunkedRequest(int client_fd) {
	// Read the request already read from the client
	(void)client_fd;
}

/**
 * Generates a timeout response
 * @return the timeout response
 */
std::string generateTimeoutResponse() {
	std::string response;
	response += "HTTP/1.1 408 Request Timeout\r\n";
	response += "Content-Type: text/html\r\n";
	response += "Content-Length: 0\r\n";
	response += "Connection: close\r\n";
	response += "\r\n";
	return response;
}

/*
** Handles timeouts
** Closes the connection if the client has timed out
*/
void PollManager::handleTimeouts() {
	for (size_t i = 1; i < _fds.size(); i++) {
		if (isServerSocket(_fds[i].fd))
			continue;
		if(!_clients[_fds[i].fd]->getRequest()->getIsReadTimeout())
			continue;
		if (handleTimeouts(_fds[i].fd) || this->handleCleanClientConnection(_fds[i].fd)){
//				std::cerr << RED << " end Server::pollConnections() : handleCleanClientConnection(" << i << ") " << RESET << __FILE__ <<":"<<__LINE__ << std::endl;
				i--;
		}
	}
}

bool PollManager::handleTimeouts(int client_fd) {
	time_t current_time = Utils::getCurrentTimeInMilliseconds();
	Client *client = _clients[client_fd];
	if (client == nullptr) {
		std::cerr << "Client not found for fd: " << client_fd << std::endl;
		return true;
	}
	time_t last_check = client->getRequest()->getLastActive() + client->getRequest()->getTimeoutValue();
	if ( current_time > last_check){
		std::string timeoutResponse = generateTimeoutResponse();
		send(client_fd, timeoutResponse.c_str(), timeoutResponse.size(), 0);
		client->setIsclose();
		std::cerr << DIM <<DARKRED << "PollManager::handleTimeouts(int client_fd) Connexion fermée (inactivité) : " << RESET << "client: " << client_fd << std::endl;
		handleCleanClientConnection(client_fd);
		return true;
	}
	_last_check = current_time;
	return false;
}