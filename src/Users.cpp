/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:51:49 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/17 11:27:00 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Users.cpp"

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

std::string Users::getBuffer() const
{
	return this->buffer;	
}