/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:51:49 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/14 15:00:28 by sal-zuba         ###   ########.fr       */
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

