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

struct	C_Users{
	std::string	nickName;
	int	flag;
};

class Channel
{
	private:
		int						limit;
		// int						Limitf;
		int						Topicf;
		int						invitef;
		std::string				Mode;
		std::string				Name;
		std::string				Password;
		std::string				Topic;
		std::string				Quote;
	public:
		Channel(std::string name);
		Channel(const Channel &cp);
		~Channel();
		Channel	&operator=(const Channel &og);

		void	setName(std::string name);
		void	setPassword(std::string password);
		void	setTopic(std::string topic);
		void	setLimit(int	limit);
		void	setQuote(std::string Quote);
		
		std::vector<struct C_Users>	UserList;
		std::string	getName() const;
		std::string	getPassword() const;
		std::string	getTopic() const;
		std::string	getQuote() const;
		int			getLimit() const;
		int			getinvitef() const;


		void	addUsertoC(Users *user);
		void	deleteUserfromC(Users	*user);
		void	fliptoOperator(Users	*user);
		void	CheckifOP(Users *user, Channel *channel);
};