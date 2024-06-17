/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:34:46 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/17 12:44:38 by sal-zuba         ###   ########.fr       */
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

#include "Users.hpp"

class Users;

class Channel
{
	private:
		std::map<std::string , int> Glist;
		std::vector<Users *>	UserList;
		int						limit;
		std::string				Name;
		std::string				Password;
		std::string				Topic;
	public:
		Channel(std::string name);
		Channel(const Channel &cp);
		~Channel();
		Channel	&operator=(const Channel &og);

		
}