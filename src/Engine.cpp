/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:29:14 by rmehadje          #+#    #+#             */
/*   Updated: 2024/06/14 12:29:18 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void  Server::init()
{
   char  name[1024];

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

void  Server::start()
{
   int   activity;
   while (1)
   {
      activity = poll(&(this->Fds[0]), this->Fds.size(), -1);
      if (activity < 0) {
         std::cout << "Error: poll: " << strerror(errno) << std::endl;
         exit(EXIT_FAILURE);
      }

      for (size_t i = 0; i < this->Fds.size(); ++i) {
         if (this->Fds[i].revents & POLLIN) {
            if (this->Fds[i].fd == this->ServerSocket) {
               if (addNewClient() == -1)
                  continue ;
            }
            else {
               user = getUserByFd(this->Fds[i].fd);
               if (user)
                  handleMsg(user, i);
            }
         }
         if (i < this->Fds.size() && (this->Fds[i].revents & POLLOUT))
            send_2usr(this->Fds[i].fd); 
      }
   }
}
