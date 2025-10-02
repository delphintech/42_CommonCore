/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:47:11 by nbrigui           #+#    #+#             */
/*   Updated: 2025/01/15 18:20:10 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <cstring>//for strcpy
#include <vector>
#include <cstdlib>

class Env {
	private:
		std::map<std::string, std::string> envVariables;

	public:
		// Ajouter une variable d'environnement
		void add(const std::string& key, const std::string& value) {
			envVariables[key] = value;
		}

		// Obtenir les variables d'environnement sous forme de tableau pour execve()
		std::vector<char*> toEnvArray() const {
			std::vector<char*> envArray;
			for (std::map<std::string, std::string>::const_iterator it = envVariables.begin(); it != envVariables.end(); ++it){
				std::string env = it->first + "=" + it->second;
				char* envEntry = new char[env.size() + 1];
				std::strcpy(envEntry, env.c_str());
				envArray.push_back(envEntry);
			}
			envArray.push_back(NULL); // Terminateur NULL
			return envArray;
		}

		// Nettoyer les variables d'environnement
		static void cleanEnvArray(std::vector<char*>& envArray) {
			for (std::vector<char*>::const_iterator it = envArray.begin(); it != envArray.end(); ++it) {
				delete[] *it;
			}
		}
};
