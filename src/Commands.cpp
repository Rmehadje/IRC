#include "../include/Server.hpp"
#include "../include/Replies.hpp"

void	Server::AddPtoUser(Command cmd, Users *user){
	std::string pword = cmd.Rest;
	if (user->getStatus() == 1){
		if (!pword.empty() && pword == this->Password){
			user->setStatus(2);
		}
		if (pword.empty())
			user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName));
		else{
			user->setBuffer(ERR_PASSWDMISMATCH(user->getHostname()));
		}
	}
	else if (user->getStatus() > 2){
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
		// std::string tmp = "@" + cmd.Rest;
		user->setNickname(cmd.Rest);
		if (user->getStatus() == 3 && user->getUsername() == "*")
			return ;
		user->setStatus(user->getStatus() + 1);
	}
	if (user->getStatus() == 4)
		return (user->setBuffer(RPL_WELCOME(this->getHost(), user->getUsername(), user->getHostname(), user->getNickname()))); //rpl_welcome;
	return ;
}

