/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:29:39 by dabouab           #+#    #+#             */
/*   Updated: 2025/02/05 15:00:14 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Location.hpp"
#include <sstream> 

Location::Location() :  _auto_index(false) , _methods(), _client_max_body_size(0) {
	_uri = "/";
	_root = "";
	_index = "";
	_return = "";
	_alias = "";
	_cgi_path = "";
	_cgi_ext = "";
	_upload_store = "";
	//par defaut on autorise toutes les methodes
	_methods.push_back("GET");
	_methods.push_back("POST");
	//_methods.push_back("PUT");
	//_methods.push_back("DELETE");
	_methods.push_back("OPTIONS");
	_methods.push_back("HEAD");
}

// ----- Create the Location according to the config file -----
Location::Location(std::fstream& conf_file, std::string uri, std::string root) 
	: _uri(uri), _root(""/* root */), _auto_index(false), _methods() , _client_max_body_size(0)
{
	std::string		line;
	(void)root;
	
	while (std::getline(conf_file, line))
	{
		Utils::String::trim(line, (char *)"\t\n\r\v\f ");
		if (!Utils::String::get_between(line, "", " ").compare("root"))
			_root = Utils::String::get_between(line, "root", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("index"))
			_index = Utils::String::get_between(line, "index", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("auto_index"))
		{
			if (!Utils::String::get_between(line, "index", ";").compare("on"))
				_auto_index = true;
		}
		else if (!Utils::String::get_between(line, "", " ").compare("allow_methods"))
			_methods = Utils::String::str_to_vect(Utils::String::get_between(line, "allow_methods", ";"), ' ');
		else if (!Utils::String::get_between(line, "", " ").compare("return"))
			_return = Utils::String::get_between(line, "return", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("alias"))
			_alias = Utils::String::get_between(line, "alias", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("cgi_path"))
			_cgi_path = Utils::String::get_between(line, "cgi_path", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("cgi_ext"))
			_cgi_ext = Utils::String::get_between(line, "cgi_ext", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("upload_store"))
			_upload_store = Utils::String::get_between(line, "upload_store", ";");
		else if (!Utils::String::get_between(line, "", " ").compare("client_max_body_size"))
			//_client_max_body_size = Utils::String::get_between(line, "client_max_body_size", ";");
			_client_max_body_size = Utils::String::str_to_int((char *)Utils::String::get_between(line, "client_max_body_size", ";").c_str());

		if (_cgi_ext != "" && _cgi_path != "")
			setCgiInterpreters(_cgi_ext, _cgi_path);
		if (line.find("}") != std::string::npos)
			break ;
	}
	if (_index.empty())
		_index = "";//_root;
}

Location::~Location() {}

Location & Location::operator=(const Location &arg) {
	if (this == &arg) {
		return *this;
	}
	_uri = arg._uri;
	_root = arg._root;
	_index = arg._index;
	_auto_index = arg._auto_index;
	_methods = arg._methods;
	_return = arg._return;
	_alias = arg._alias;
	_cgi_ext = arg._cgi_ext;
	_cgi_path = arg._cgi_path;
	_cgiInterpreters = arg._cgiInterpreters;
	_upload_store = arg._upload_store;
	_client_max_body_size = arg._client_max_body_size;
	return *this;
}

Location::Location(const Location &arg) {
	_uri = arg._uri;
	_root = arg._root;
	_index = arg._index;
	_auto_index = arg._auto_index;
	_methods = arg._methods;
	_return = arg._return;
	_alias = arg._alias;
	_cgi_ext = arg._cgi_ext;
	_cgi_path = arg._cgi_path;
	_cgiInterpreters = arg._cgiInterpreters;
	_upload_store = arg._upload_store;
	_client_max_body_size = arg._client_max_body_size;
}

void	Location::display() {
	std::cout << "\t\turi: " << this->_uri << std::endl;
	std::cout << "\t\troot: " << this->_root << std::endl;
	std::cout << "\t\tindex: " << this->_index << std::endl;
	std::cout << "\t\tauto_index: " << std::boolalpha << this->_auto_index << std::noboolalpha << std::endl;
	std::cout << "\t\tmethods: ";
	for (size_t i = 0; i < _methods.size(); i++) {
		std::cout << _methods[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "\t\treturn: " << this->_return << std::endl;
	std::cout << "\t\talias: " << this->_alias << std::endl;
	std::cout << "\t\tcgi_path: " << this->_cgi_path << std::endl;
	std::cout << "\t\tcgi_ext: " << this->_cgi_ext << std::endl;
	std::cout << "\t\tupload_store: " << this->_upload_store << std::endl;
	if (this->_client_max_body_size == 0)
		std::cout << "\t\tclient_max_body_size: " <<  "no define"  << std::endl;
	else
		std::cout << "\t\tclient_max_body_size: " << this->_client_max_body_size << std::endl;
}

bool Location::match(const std::string &uri)const {
	return uri.find(_uri) != std::string::npos;
};

const std::string &Location::getRoot() const {
	return _root;
};

const std::string &Location::getIndex() const {
	return _index;
};

const std::string &Location::getUri() const {
	return _uri;
};
bool Location::getAutoIndex() const {
	return _auto_index;
};

const std::vector<std::string>	&Location::getMethods() const {
	return _methods;
};

const std::string		&Location::getCgiPaths() const {
	return _cgi_path;
};

const std::string		&Location::getCgiExts() const {
	return _cgi_ext;
};

const std::string		&Location::getAlias() const {
	return _alias;
};


std::map<std::string, std::string>	&Location::getCgiInterpreters() {
	return _cgiInterpreters;
};

void Location::setCgiInterpreters(std::string cgi_ext, std::string cgi_path) { 
	//split the cgi_ext and cgi_path at each space
	std::vector<std::string> exts = Utils::String::str_to_vect(cgi_ext, ' ');
	std::vector<std::string> paths = Utils::String::str_to_vect(cgi_path, ' ');
	for (size_t i = 0; i < exts.size(); i++) {
		_cgiInterpreters[exts[i]] = paths[i];
	}
};

std::string &Location::getCgiPath(std::string ext) {
	if (ext == "")
		return _nullString;
	if(_cgiInterpreters.find(ext) == _cgiInterpreters.end())
		return _nullString;
	return _cgiInterpreters[ext];
};

void Location::setUploadDir(std::string uploadDir) {
	_upload_store = uploadDir;
};

const std::string &Location::getUploadDir() const {
	return _upload_store;
};

int Location::getClientMaxBodySize() const {
	return _client_max_body_size;
};

std::string &Location::getReturn() {
	return _return;
};