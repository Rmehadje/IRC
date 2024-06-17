/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:01:11 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/17 13:40:09 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Lib.hpp"
#include <unistd.h>

class	Users
{
	private:
		std::string Nickname;
		std::string	Username;
		std::string Hostname;
		std::string Realname;
		std::string Mode;
		int			Socket;
		int			Status;
		std::string buffer;
		std::string	cmd;
		//myb buffer
	public:
		Users(std::string hostname, int socket);
		~Users();
		Users(const Users &cp);
		Users &operator=(const Users &cp);

		std::string getNickname() const;
		std::string getUsername() const;
		std::string getHostname() const;
		std::string getRealname() const;
		std::string getMode() const;
		int			getSocket() const;
		int			getStatus() const;
		std::string		getBuffer() const;
		std::string		getCmd() const;
		
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setHostname(std::string hostname);
		void setRealname(std::string realname);
		void setMode(std::string mode);
		void setSocket(int socket);
		void setStatus(int status);
		void setBuffer(std::string msg);
		void setCmd(std::string msg);

		void	clearCmd();
};