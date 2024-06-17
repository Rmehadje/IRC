/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:51:49 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/17 12:21:06 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Users.hpp"

Users::Users(std::string name, int socket)
{
	Hostname = name;
	Nickname = "*";
	Username = "*";
	Realname = "*";
	Mode = "*";
	Socket = socket;
	Status = 0;
}

Users::~Users()
{
	close(Socket);
}

std::string Users::getNickname() const
{
	return this->Nickname;	
}

std::string Users::getBuffer() const
{
	return this->buffer;	
}

std::string	Users::getUsername() const{
	return (this->Username);
}

std::string	Users::getHostname() const{
	return (this->Hostname);
}

std::string	Users::getRealname() const{
	return (this->Realname);
}

std::string	Users::getMode() const{
	return (this->Mode);
}

int	Users::getSocket() const{
	int	sock = this->Socket;
		return (sock);
}

int	Users::getStatus() const{
	int	stat = this->Status;
	return (stat);
}


void	Users::setNickname(std::string nickname){
	this->Nickname = nickname;
}
void	Users::setUsername(std::string username){
	this->Username = username;
}
void	Users::setHostname(std::string hostname){
	this->Hostname = hostname;
}
void	Users::setRealname(std::string realname){
	this->Realname = realname;
}
void	Users::setMode(std::string mode){
	this->Mode = mode;
}
void	Users::setSocket(int	socket){
	this->Socket = socket;
}
void	Users::setStatus(int status){
	this->Status = status;
}

Users::Users(const Users &cp){
	if (this != &cp){
		setHostname(cp.getHostname());
		setNickname(cp.getNickname());
		setUsername(cp.getUsername());
		setRealname(cp.getRealname());
		setMode(cp.getMode());
		setSocket(cp.getSocket());
		setStatus(cp.getStatus());
	}
	std::cout << "copy constructor has been called" << std::endl;
}

Users &Users::operator=(const Users &cp){
	if (this != &cp)
	{
		setHostname(cp.getHostname());
		setNickname(cp.getNickname());
		setUsername(cp.getUsername());
		setRealname(cp.getRealname());
		setMode(cp.getMode());
		setSocket(cp.getSocket());
		setStatus(cp.getStatus());
	}
	std::cout << "copy assignment constructor has been called" << std::endl;
	return (*this);
}