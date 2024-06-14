/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:27:19 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/14 12:24:42 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	Server::init()
{
	char	name[1024];

	if (gethostname(name, sizeof(name)) == -1){
		std::cerr << RED <<"name problem" << strerror(errno) << DEFAULT <<std::endl;
		exit (EXIT_FAILURE);
	}
	setHost(name);
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == -1) {
		std::cerr << "Error: socket: " << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	int opt = 1;
	if (setsockopt(this->ServerSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))
			== -1) {
		std::cerr << "Error: setsockopt: " << strerror(errno) << std::endl;
		close(this->ServerSocket);
		exit(EXIT_FAILURE);
	}
	if (fcntl(this->ServerSocket, F_SETFL, O_NONBLOCK) == -1) {
		std::cerr << "Error: fcntl: " << strerror(errno) << std::endl;
		close(this->ServerSocket);
		exit(EXIT_FAILURE);
	}
		struct sockaddr_in serverAdr;
	std::memset(&serverAdr, 0, sizeof(serverAdr));
	serverAdr.sin_family = AF_INET;
	serverAdr.sin_addr.s_addr = INADDR_ANY;
	serverAdr.sin_port = htons(getPort());
	if (bind(this->ServerSocket, (struct sockaddr *)&serverAdr, sizeof(serverAdr))
			== -1) {
		std::cerr << "Error: bind: " << strerror(errno) << std::endl;
		close(this->ServerSocket);
		exit(EXIT_FAILURE);			
	}
	
	if (listen(this->ServerSocket, 128) == -1) {
		std::cerr << "Error: listen: " << strerror(errno) << std::endl;
		close(this->ServerSocket);
		exit(EXIT_FAILURE);
	}
	
	struct pollfd sfd;
	std::memset(&sfd, 0, sizeof(sfd));
	sfd.fd = this->ServerSocket;
	sfd.events = POLLIN;
	addPfds(sfd);
}

void	Server::start()
{
	
}