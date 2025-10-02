#include "class/DomainConfig.hpp"

DomainConfig::DomainConfig() : _sfd(-1), _error_page() {}

// ----- Create the DomainConfig according to the config file -----
DomainConfig::DomainConfig(std::fstream &conf_file)
	: _sfd(-1), _host("0.0.0.0", INADDR_ANY),  _error_page()
{
	this->_send_timeout = 30;
	std::string		line;
	this->_server_name.push_back(std::string());// = std::vector<std::string>();
	this->_client_max_body_size = 0;
	
	while (std::getline(conf_file, line))
	{
		Utils::String::trim(line, (char *)"\t\n\r\v\f ");
		if (!Utils::String::get_between(line, "", " ").compare("listen"))
			_listen = Utils::String::str_to_int((char *)Utils::String::get_between(line, "listen", ";").c_str());
		else if (!Utils::String::get_between(line, "", " ").compare("host"))
		{
			_host.first = Utils::String::get_between(line, "host", ";");
			setHost(_host.first);
		}
		else if (!Utils::String::get_between(line, "", " ").compare("server_name"))
			_server_name = Utils::String::str_to_vect(Utils::String::get_between(line, "server_name", ";"), ' ');
		/* else if (!Utils::String::get_between(line, "", " ").compare("error_page"))
		{
			std::vector<std::string>	temp = Utils::String::str_to_vect(Utils::String::get_between(line, "error_page", ";"), ' ');
			_error_page.first = Utils::String::str_to_int((char *)temp[0].c_str());
			if (temp.size() > 1)
				_error_page.second = temp[1];
		} */

		else if (!Utils::String::get_between(line, "", " ").compare("error_page"))
		{
			std::vector<std::string>	temp_err = Utils::String::str_to_vect(Utils::String::get_between(line, "error_page", ";"), ' ');
			if (temp_err.size() > 1)
				setErrorPage(Utils::String::str_to_int((char *)temp_err[0].c_str()), temp_err[1]);
		}
		else if (!Utils::String::get_between(line, "", " ").compare("client_max_body_size"))
			_client_max_body_size = Utils::String::str_to_int((char *)Utils::String::get_between(line, "client_max_body_size", ";").c_str());
		else if (!Utils::String::get_between(line, "", " ").compare("root"))
			_root = Utils::String::get_between(line, "root", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("index"))
			_index = Utils::String::get_between(line, "index", ";");
		else if (line.find("location") != std::string::npos && line.find("{") != std::string::npos)
		{
			this->_locations.push_back(Location(conf_file, Utils::String::get_between(line, "location", "{"), this->_root));
			continue ;
		}
		else if(line.find("add_header") != std::string::npos)
		{
			std::vector<std::string>	temp = Utils::String::str_to_vect(Utils::String::get_between(line, "add_header", ";"), ' ');
			if (temp.size() > 1)
				setAddHeaders(temp[0], temp[1]);
		}



		if (line.find("}") != std::string::npos)
			break ;
	}
	createSetLocation();
}
DomainConfig & DomainConfig::operator=(const DomainConfig &arg) {
	if (this == &arg) {
		return *this;
	}
	this->_sfd = arg._sfd;
	this->_listen = arg._listen;
	this->_host = arg._host;
	this->_server_name = arg._server_name;
	this->_error_page = arg._error_page;
	this->_client_max_body_size = arg._client_max_body_size;
	this->_root = arg._root;
	this->_index = arg._index;
	this->_locations = arg._locations;
	this->_addHeaders = arg._addHeaders;
	this->_sorted_paths = arg._sorted_paths;
	this->_nullLocation = arg._nullLocation;
	this->_send_timeout = arg._send_timeout;
	return *this;
}
DomainConfig & DomainConfig::operator=(const DomainConfig *arg) {
	if (this == arg) {
		return *this;
	}
	this->_sfd = arg->_sfd;
	this->_listen = arg->_listen;
	this->_host = arg->_host;
	this->_server_name = arg->_server_name;
	this->_error_page = arg->_error_page;
	this->_client_max_body_size = arg->_client_max_body_size;
	this->_root = arg->_root;
	this->_index = arg->_index;
	this->_locations = arg->_locations;
	this->_addHeaders = arg->_addHeaders;
	this->_sorted_paths = arg->_sorted_paths;
	this->_nullLocation = arg->_nullLocation;
	this->_send_timeout = arg->_send_timeout;
	return *this;
}

DomainConfig::DomainConfig(const DomainConfig &arg)
	: _sfd(arg._sfd), _listen(arg._listen), _host(arg._host), _server_name(arg._server_name),
	_error_page(arg._error_page), _client_max_body_size(arg._client_max_body_size), _root(arg._root),
	_index(arg._index), _locations(arg._locations), _addHeaders(arg._addHeaders), _sorted_paths(arg._sorted_paths), _nullLocation(arg._nullLocation) {
		this->_send_timeout = arg._send_timeout;
}

DomainConfig::DomainConfig(const DomainConfig *arg) :
	_sfd(arg->_sfd), _listen(arg->_listen), _host(arg->_host), _server_name(arg->_server_name),
	_error_page(arg->_error_page), _client_max_body_size(arg->_client_max_body_size), _root(arg->_root),
	_index(arg->_index), _locations(arg->_locations), _addHeaders(arg->_addHeaders), _sorted_paths(arg->_sorted_paths), _nullLocation(arg->_nullLocation) {
		this->_send_timeout = arg->_send_timeout;
}

// Server::Server(const Server &arg) {
// 	this->_sfd = arg._sfd;
// 	this->_host = arg._host;
// 	this->_server_name = arg._server_name;
// 	this->_error_page = arg._error_page;
// 	this->_client_max_body_size = arg._client_max_body_size;
// 	this->_root = arg._root;
// 	this->_index = arg._index;
// 	this->_locations = arg._locations;
// }

void	DomainConfig::display() {
	std::cout << "\tfd: " << this->_sfd << std::endl;
	std::cout << "\tlisten: " << this->_listen << std::endl;
	std::cout << "\thost: " << this->_host.first << " (" << this->_host.second << ")" << std::endl;
	std::cout << "\tserver name: ";
	std::cout << std::endl;
	std::cout << "\taddheaders: ";
	std::cout << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = _addHeaders.begin(); it != _addHeaders.end(); ++it) {
		std::cout <<"\t\t" << it->first << " " << it->second << std::endl;
	}

	for (size_t i = 0; i < _server_name.size(); i++) {
		std::cout << _server_name[i] << " ";
	}
	std::cout << std::endl;
	//std::cout << "\terror pages: " << _error_page.first << " " << _error_page.second << std::endl;
	
	std::cout << "\terror pages: ";
	for (std::map<int, std::string>::const_iterator it = _error_page.begin(); it != _error_page.end(); ++it) {
		std::cout <<"\t\t" << it->first << " " << it->second << std::endl;
	}
	std::cout << "\tclient_max_body_size: " << this->_client_max_body_size << std::endl;
	std::cout << "\troot: " << this->_root << std::endl;
	std::cout << "\tindex: " << this->_index << std::endl;
	for (size_t i = 0; i < _locations.size(); i++) {
		std::cout << "\tLocation " << i + 1 << " {" << std::endl;
		_locations[i].display();
		std::cout << "\t}" << std::endl;
	}
}

DomainConfig::~DomainConfig() {}

// ---------- GETTERS ----------
int								DomainConfig::getFd() { return (this->_sfd); }
int								DomainConfig::getListen() const { return (this->_listen); }
std::pair<std::string, long>	DomainConfig::getHost() const { return (this->_host); }
std::vector<std::string>		DomainConfig::getServer_name() const { return (this->_server_name); }
std::map<int,std::string>		DomainConfig::getError_page() const { return (this->_error_page); }
int								DomainConfig::getClient_max_body_size() const { return (this->_client_max_body_size); }
std::string						DomainConfig::getRoot() const { return (this->_root); }
std::string						DomainConfig::getIndex() const { return (this->_index); }
std::vector<Location>   		DomainConfig::getLocations() const { return (this->_locations); }

// ---------- SETTERS ----------

void	DomainConfig::setHost(std::string ip) {
	std::vector<std::string>	vect;
	int							pow;
	long						result = 0;

	vect = Utils::String::str_to_vect(ip, '.');
	pow = vect.size() - 1;
	for (int i = pow; i >= 0; i--) {
		result += Utils::String::str_to_int(vect[pow - i]) * (std::pow(256, i));
	}
	this->_host.second = result;
}

DomainConfig &DomainConfig::getDomainConfig() {
	return *this;
}

DomainConfig *DomainConfig::clone() {
	return new DomainConfig(*this);
}

const std::map<std::string, std::string> &DomainConfig::getAddHeaders() const{
	return _addHeaders;
}

void DomainConfig::setAddHeaders(std::string key, std::string value) {
	_addHeaders[key] = value;
}

const std::map<int, std::string> &DomainConfig::getErrorPages() const{
	return _error_page;
}

void DomainConfig::setErrorPage(int key, std::string value) {
	_error_page[key] = value;
}
void DomainConfig::createSetLocation() {
	std::vector<Location>::const_iterator ite = _locations.end();
	//creatate a pair of path and location
	std::vector<std::pair<std::string, Location> > locations;
	for (std::vector<Location>::const_iterator it = _locations.begin(); it != ite; ++it) {
		locations.push_back(std::make_pair(it->getUri(), *it));
	}
	//sort the pair by path use a set<pair> :: std::set<std::string,std::string> to sort the pair by path
	//for reverse order, use std::set<std::string, std::greater<std::string> >
	//std::set<std::string, std::greater<std::string> >  sorted_paths;
	for (std::vector<std::pair<std::string, Location> >::const_iterator it = locations.begin(); it != locations.end(); ++it) {
		_sorted_paths.insert(it->first);
	}
/* 	std::cerr << ORANGE<< "[debug] DomainConfig::createSetLocation() " << RESET << __FILE__ << ":" << __LINE__ << std::endl;
	std::cerr << BLUE << "[debug] sorted_paths.size() " << _sorted_paths.size() << RESET << std::endl;
	for (std::set<std::string>::const_iterator it = _sorted_paths.begin(); it != _sorted_paths.end(); ++it) {
		std::cout << "[debug] -- path: " << *it << std::endl;
	}  */
	_nullLocation = Location();
}

const Location &DomainConfig::getLocation(const std::string &uri) const{
	for (std::set<std::string>::const_iterator it = _sorted_paths.begin(); it != _sorted_paths.end(); ++it) {
	//	std::cout << "path: " << *it << std::endl;

		//1--priorite a la recgerche par extention
		//location : ~* \.(jpg|jpeg|png|gif|ico)
		std::string specificPrefix = *it;
		if ((uri.find(".") != std::string::npos)&&(specificPrefix.find(("~* \\.(")) != std::string::npos))
		{
		//	std::cerr << ORANGE << "[debug] DomainConfig::getLocation(const std::string &uri) " << RESET << __FILE__ << ":" << __LINE__ << std::endl;
		//	std::cerr << BLUE << "[debug] specificPrefix.find(*it) " << RESET << std::endl;
			//get the extension from uri
			std::string ext = uri.substr(uri.find_last_of(".") + 1);
		//	std::cerr << BLUE << "[debug] ext " << RESET << ext << std::endl;
			//get the extension from specificPrefix
			std::string exts = specificPrefix.substr(specificPrefix.find_last_of("(") + 1, specificPrefix.find_last_of(")") - specificPrefix.find_last_of("(") - 1);
		//	std::cerr << BLUE << "[debug] exts " << RESET << exts << std::endl;
			//check if the extension is in the list of extensions
			if (exts.find(ext) != std::string::npos)
			{
		//		std::cerr << BLUE << "[debug] exts.find(ext) " << RESET << std::endl;
				std::vector<Location>::const_iterator iteLoc = _locations.end();
				for (std::vector<Location>::const_iterator itLoc = _locations.begin(); itLoc != iteLoc; ++itLoc) {
					if (itLoc->getUri() == *it) {
						return *itLoc;
					}
				}
			}
		}

		//2--sinon recherche par prefix
		if (uri == *it || uri.find(*it) != std::string::npos) {
 			//warning :  uri == /test  is not /testHTTP or /test.ext
			//but     :  uri == /test/ is /test/HTTP or /test/HTTP/.. or /test
			//check if the uri is the same as the location uri
			std::string prefix = *it;
			if (uri == prefix || (uri.find(prefix + "/") != std::string::npos) || (prefix == "/")) {
			}
			else {
				continue;
			}

			std::vector<Location>::const_iterator iteLoc = _locations.end();
			for (std::vector<Location>::const_iterator itLoc = _locations.begin(); itLoc != iteLoc; ++itLoc) {
				if (itLoc->getUri() == *it) {
					return *itLoc;
				}
			}
		}
	}
	//3--sinon return nullLocation if no location found
	return _nullLocation;
}
const Location &DomainConfig::getLocation(const std::string &uri, const std::string &method) const{
	
	for (std::set<std::string>::const_iterator it = _sorted_paths.begin(); it != _sorted_paths.end(); ++it) {
		//std::cout << "path: " << *it << std::endl;
		std::string specificPrefix = *it;

		//0--priorite a la recherche par path && extention
		//location ~/directory/ ~* \.bla
		if ((uri.find(".") != std::string::npos)&&(specificPrefix.find(("~/")) != std::string::npos))
		{
		//	std::cerr << ORANGE << "[debug] DomainConfig::getLocation(const std::string &uri) " << RESET << __FILE__ << ":" << __LINE__ << std::endl;
		//	std::cerr << BLUE << "[debug] specificPrefix.find(*it)    ~* .bla   "<< *it << RESET << std::endl;
			//get the extension from uri
			std::string ext = uri.substr(uri.find_last_of(".") + 1);
		//	std::string extractpath = uri.substr(0, uri.find_last_of("/") + 1);
		//	std::cerr << BLUE << "[debug] ext " << RESET << ext << std::endl;
			//get the uri from specificPrefix
			std::string extracturi = specificPrefix.substr(specificPrefix.find("~/")+1 , specificPrefix.find_last_of("/")  - specificPrefix.find("~/") - 1);
			
		//	std::cerr << BLUE << "[debug] (specificPrefix) " << RESET << specificPrefix << std::endl;
		//	std::cerr << BLUE << "[debug] (extracturi) " << RESET << extracturi << std::endl;
			//get the extension from specificPrefix
			std::string exts = specificPrefix.substr(specificPrefix.find_last_of("(") + 1, specificPrefix.find_last_of(")") - specificPrefix.find_last_of("(") - 1);
		//	std::cerr << BLUE << "[debug] exts " << RESET << exts << std::endl;
			//check if the extension is in the list of extensions
		//	std::cerr << BLUE << "[debug] (ext) " << RESET << ext << std::endl;
			if (uri.find(extracturi)!= std::string::npos && exts.find(ext) != std::string::npos)
			{
			//	std::cerr << BLUE << "[debug] exts.find(ext) " << RESET << std::endl;
				std::vector<Location>::const_iterator iteLoc = _locations.end();
				for (std::vector<Location>::const_iterator itLoc = _locations.begin(); itLoc != iteLoc; ++itLoc) {
					if (itLoc->getUri() == *it) {
						if (itLoc->getMethods().empty() || std::find(itLoc->getMethods().begin(), itLoc->getMethods().end(), method) != itLoc->getMethods().end())
							return *itLoc;
					}
				}
			}
		}


		//1--priorite a la recgerche par extention
		//location : ~* \.(jpg|jpeg|png|gif|ico)
		if ((uri.find(".") != std::string::npos)&&(specificPrefix.find(("~* \\.(")) != std::string::npos))
		{
		//	std::cerr << ORANGE << "[debug] DomainConfig::getLocation(const std::string &uri) " << RESET << __FILE__ << ":" << __LINE__ << std::endl;
		//	std::cerr << BLUE << "[debug] specificPrefix.find(*it) " << RESET << std::endl;
			//get the extension from uri
			std::string ext = uri.substr(uri.find_last_of(".") + 1);
		//	std::cerr << BLUE << "[debug] ext " << RESET << ext << std::endl;
			//get the extension from specificPrefix
			std::string exts = specificPrefix.substr(specificPrefix.find_last_of("(") + 1, specificPrefix.find_last_of(")") - specificPrefix.find_last_of("(") - 1);
		//	std::cerr << BLUE << "[debug] exts " << RESET << exts << std::endl;
			//check if the extension is in the list of extensions
			if (exts.find(ext) != std::string::npos)
			{
		//		std::cerr << BLUE << "[debug] exts.find(ext) " << RESET << std::endl;
				std::vector<Location>::const_iterator iteLoc = _locations.end();
				for (std::vector<Location>::const_iterator itLoc = _locations.begin(); itLoc != iteLoc; ++itLoc) {
					if (itLoc->getUri() == *it) {
						if (itLoc->getMethods().empty() || std::find(itLoc->getMethods().begin(), itLoc->getMethods().end(), method) != itLoc->getMethods().end())
							return *itLoc;
					}
				}
			}
		}

		//2--sinon recherche par prefix
		size_t pos =  uri.find(*it);
		if (uri == *it || (pos != std::string::npos && pos == 0)) {
 			//warning :  uri == /test  is not /testHTTP or /test.ext
			//but     :  uri == /test/ is /test/HTTP or /test/HTTP/.. or /test
			//check if the uri is the same as the location uri
			std::string prefix = *it;
			if (uri == prefix || (uri.find(prefix + "/") != std::string::npos) || (prefix == "/")) {
			}
			else {
				continue;
			}

			std::vector<Location>::const_iterator iteLoc = _locations.end();
			for (std::vector<Location>::const_iterator itLoc = _locations.begin(); itLoc != iteLoc; ++itLoc) {
				if (itLoc->getUri() == *it) {
					return *itLoc;
				}
			}
		}
	}
	//3--sinon return nullLocation if no location found
	return _nullLocation;
}

size_t DomainConfig::getSendTimeout() const{
	return _send_timeout;
}

DomainConfig &DomainConfig::setSendTimeout(size_t send_timeout){
	_send_timeout = send_timeout;
	return *this;
}
