/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:59:14 by dabouab           #+#    #+#             */
/*   Updated: 2025/01/10 18:40:32 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_H
# define WEBSERV_H

#include <iostream>
#include <cerrno>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <iterator>
#include <utility>

#include "Utils/Utils.hpp"

# define COLOR(nb) "\e["#nb"m"

#endif