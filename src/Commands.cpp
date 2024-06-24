#include "../include/Server.hpp"
#include "../include/Replies.hpp"

void	Server::AddPtoUser(Command cmd, Users *user){
	std::string pword = cmd.Rest;
	if (user->getStatus() == 1){
		if (!pword.empty() && pword == this->Password){
			user->setStatus(2);
			user->setBuffer(RPL_PASS(user->getHostname()));
		}
		else if (pword.empty())
			user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName));
		else {
			user->setBuffer(ERR_PASSWDMISMATCH(user->getHostname()));
		}
	}
	else if (user->getStatus() >= 2){
		user->setBuffer(ERR_ALREADYREGISTERED(user->getHostname()));
	}
}

void	Server::AddNicktoUser(Command cmd, Users *user){
	if (user->getStatus() >= 2)
	{
		std::string Nick = cmd.Rest;
		for (std::vector<Users *>::iterator it = this->AllUsers.begin(); it != this->AllUsers.end(); it++){
				if ((*it)->getNickname() == Nick){
					user->setBuffer(ERR_NICKNAMEINUSE(user->getHostname(), Nick));
					return ;
				}
		}
		user->setNickname(cmd.Rest);
		user->setBuffer(RPL_NICK(user->getHostname(), user->getNickname()));
		if (user->getStatus() == 3 && user->getUsername() == "*")
			return ;
		user->setStatus(user->getStatus() + 1);
	}
	if (user->getStatus() == 4)
		return (user->setBuffer(RPL_WELCOME(this->getHost(), user->getUsername(), user->getHostname(), user->getNickname()))); //rpl_welcome;
	return ;
}

void	Server::CapInit(Command cmd, Users *user)
{
	if (cmd.CmdName == "CAP" && user->getStatus() == 0)
	{
		if (cmd.Rest == "LS")
		{
			user->setStatus(1);
			user->setBuffer(RPL_CAP(user->getHostname()));
		}
	}
	else if (user->getStatus())
	{
		if (cmd.Rest == "LS")
			user->setBuffer(RPL_CAP(user->getHostname()));
	}
}

void	Server::RegisterUser(Command cmd, Users *user)
{
	if (user->getStatus() >= 2)
	{
		std::vector<std::string>::iterator it = cmd.params.begin();
		std::string username = *it;
		it = cmd.params.end();
		it--;
		std::string realname = *it;
		realname = realname.substr(1, realname.length() - 1);
		user->setRealname(realname);
		user->setUsername(username);
		if (user->getStatus() == 3 && user->getNickname() == "*")
			return ;
		user->setStatus(user->getStatus() + 1);
	}
	if (user->getStatus() == 4)
		return ; //rpl_welcome;
	return ;
}