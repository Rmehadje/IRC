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
#include "Channel.hpp"

class Users;
class Channel;
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
		std::vector<Channel *> AllChannels;
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
		void	executeCmd(Command msg, Users *user);
	
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
	
	//Commands
		void	AddPtoUser(Command cmd, Users *user);
		void	AddNicktoUser(Command cmd, Users *user);
		void	CapInit(Command cmd, Users *user);
		void	RegisterUser(Command cmd, Users *user);
		void	SendPong(Command cmd, Users *user);
		void broadcast_quit_message(Users *user, const std::string& message);
		void c_quit(Command cmd, Users *user);
};