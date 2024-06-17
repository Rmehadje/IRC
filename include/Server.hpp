/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:24 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/17 14:11:06 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <list>
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

class Users;

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
		std::vector<Users *>	AllUsers;
		Server();
	public:
		Server(int port, std::string password);
		~Server();
		Server(const Server &cp);
		Server &operator=(const Server &cp);
	
		void init();
		void start();
		void stop();
		void	addPfds(struct pollfd sfd);
		void	addUser(Users *user);
		int	addNewClient();
		void	send_2usr(int fd);
		void	removePfds(struct pollfd sfd);
		void	removeUserFromServer(Users *user);
		void	handleMsg(Users *user);
	
	//Setters
		void	setHost(std::string name);
		void	setStatus(bool flag);
		void	setBytesReceived(int BytesReceived);

	//Getters
		std::string getHost() const;
		bool	getStatus() const;
		int	getPort() const;
		Users*	getUserByFd(int fd);
		ssize_t getBytesReceived();
};