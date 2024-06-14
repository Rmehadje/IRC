/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:24 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/14 12:23:36 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>

#include "Lib.hpp"
#include "Users.hpp"

// class Users;

class Server
{
	private:
		int	Port;
		std::string Password;
		bool			ServerStatus;
		std::string	Host;
		char		buffer[1024];
		std::vector<struct pollfd>	Fds;
		ssize_t	BytesReceived;
		int		ServerSocket;
		Server();
	public:
		Server(int port, std::string password);
		~Server();
		Server(const Server &cp);
		Server &operator=(const Server &cp);
	
		void init();
		void start();
		void stop();
		std::string getHost() const;
		void	setHost(std::string name);
		void	setStatus(bool flag);
		bool	getStatus() const;
		int	getPort() const;

		
		void	addPfds(struct pollfd sfd);
};