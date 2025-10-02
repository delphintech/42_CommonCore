/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:07:39 by nbrigui           #+#    #+#             */
/*   Updated: 2025/02/05 13:04:47 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "request/AHTTPRequest.hpp"
#include "request/AHTTPChunkedRequest.hpp"
#include "request/AMultipartRequest.hpp"
#include "Utils/Utils.hpp"

class Request : public AHTTPRequest , public AHTTPChunkedRequest, public AMultipartRequest {
	private:
		bool _forceClose;
		bool _isResetRevents;
		bool _is_timeout;
		int _timeout_value;
		int _rcvbuf;
		time_t _last_active; //Timeout d'inactivité

		bool _is_read_timeout;
		time_t _timeout_last_read;// Timeout de lecture
	public:
		Request &setIsResetRevents(bool isResetRevents);
		bool getIsResetRevents() const;
		Request();
		Request(const Request &other);
		Request* operator=(Request* other);
		Request& operator=(const Request& other);
		Request *clone();
		void clear();
		~Request();
		Request &setForceClose(bool forceClose);
		bool getForceClose() const;


		void setTimeoutValue(int timeout_value);
		int getTimeoutValue() const;
		void setRcvbuf(int rcvbuf);
		int getRcvbuf() const;
		
		// Timeout d'inactivité
		void setIsTimeout(bool is_timeout);
		bool getIsTimeout() const;
		void setLastActive(time_t last_active);
		time_t getLastActive() const;

		// Timeout de lecture
		void setIsReadTimeout(bool is_read_timeout);
		bool getIsReadTimeout() const;
		void setTimeoutLastRead(time_t timeout_last_read);
		time_t getTimeoutLastRead() const;

};

