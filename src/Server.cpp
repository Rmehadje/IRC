/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:53:34 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/17 15:10:31 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server(){}

Server::Server(int port, std::string password)
{
	Port = port;
	Password = password;
	this->setStatus(true);
	std::cout << GREEN << "-------STARTING---SERVER-------" << DEFAULT << std::endl;
}

Server::~Server(){}

Server::Server(const Server &cp)
{
	*this = cp;
}

Server &Server::operator=(const Server &cp)
{
	if (this != &cp)
		*this = cp;
	return *this;
}

void Server::setHost(std::string name)
{
	Host = name;
}

std::string Server::getHost() const
{
	return this->Host;
}

bool	Server::getStatus() const
{
	return ServerStatus;
}

void	Server::setStatus(bool flag)
{
	ServerStatus = flag;
}

int	Server::getPort() const
{
	return this->Port;
}

void	Server::addPfds(struct pollfd sfd) 
{
	this->Fds.push_back(sfd);
}

void	Server::setBytesReceived(int BytesReceived)
{
	this->BytesReceived = BytesReceived;
}

ssize_t Server::getBytesReceived()
{
	return this->BytesReceived;
}

Users *Server::getUserByFd(int fd) {
	for (std::vector<Users *>::iterator it = this->AllUsers.begin(); 
			it != this->AllUsers.end(); ++it) {
		if ((*it)->getSocket() == fd)
			return *it;
	}
	return NULL;
}


void	Server::removePfds(struct pollfd sfd)
{
	for (std::vector<struct pollfd>::iterator it = this->Fds.begin(); it != this->Fds.end(); ++it) {
		if ((*it).fd == sfd.fd && ((*it).events == sfd.events)) {
			this->Fds.erase(it);
			return ;
		}
	}
}

void  Server::addUser(Users *user)
{
   for (std::vector<Users *>::iterator it = this->AllUsers.begin(); it != this->AllUsers.end();++it)
      if ((*it)->getNickname() == user->getNickname())
         return ;
   this->AllUsers.push_back(user);
}

void	Server::removeUserFromServer(Users *user)
{
	for (std::vector<pollfd>::iterator it = this->Fds.begin(); it != this->Fds.end(); it++)
	{
		if ((*it).fd == this->ServerSocket)
			continue ;
		if ((*it).fd == user->getSocket()) 
		{
			this->Fds.erase(it);
			break ;
		}
	}
	for (std::vector<Users *>::iterator it = this->AllUsers.begin(); it != this->AllUsers.end(); ++it) {
		if ((*it) == user) 
		{
			this->AllUsers.erase(it);
			break ;
		}
	}
	delete user;
}

void Server::handleMsg(Users *user)
{
	setBytesReceived(recv(user->getSocket(), this->buffer, sizeof(this->buffer), 0));
	if (getBytesReceived() <= 0) {
		if (getBytesReceived() == 0)
			std::cout << "Connection closed." << std::endl;
		else
			std::cerr << "Error: recv: " << strerror(errno) << std::endl;
		removeUserFromServer(user);
	}
	else {
		std::string msg(buffer, getBytesReceived());
		std::memset(this->buffer, '\0', sizeof(this->buffer));
		user->setCmd(msg);
		if (!Check(user->getCmd(), "\r\n"))
			return ;
		std::vector<std::string> vec = MySplit(user->getCmd(), "\r\n");
		std::string tmp = user->getCmd().substr(user->getCmd().rfind("\r\n") + 2);
		user->clearCmd();
		user->setCmd(tmp);
		for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it) {
			Command cmd = parse(*it);
			CheckCmd(cmd);
			
			// executeCmd(cont, user);
			std::cout << YELLOW << "Received: " << DEFAULT << *it << std::endl;
		}
	}
}