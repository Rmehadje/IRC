/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:01:11 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/14 12:24:33 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"

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
		//myb buffer
	public:
		Users(std::string hostname, int socket);
		~Users();
		Users(const Users &cp);
		Users &operator=(const Users &cp);

		std::string getNickname();
		std::string getUsername();
		std::string getHostname();
		std::string getRealname();
		std::string getMode();
		std::string getSocket();
		std::string getStatus();
		
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setHostname(std::string hostname);
		void setRealname(std::string realname);
		void setMode(std::string mode);
		void setSocket(int socket);
		void setStatus(int status);
		
};