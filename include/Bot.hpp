#pragma once

#include "Server.hpp"
#include <ctime>
#include <random>

class Command;
class Users;
class Server;

class Bot{
	private:
		std::string name;
	public:
		Bot(std::string name);
		~Bot();
		Bot(const Bot &cp);
		Bot &operator=(const Bot &og);

		void	setBotName(std::string name);
		std::string getBotName() const;


		void	HelpCommands(Users *user);
		void	BotCommands(Users *user);
		void	UserList(Users *user, std::vector<Users *>	&AllUsers);
		void	ChannelList(Users *user, std::vector<Channel *> &AllChannels);
		void	EightBall(Users *user);
		void	d20(Users *user);
		void	Greetings(Users *user, Channel *channel);
		void	executeBot(Command cmd, Users *user);
};