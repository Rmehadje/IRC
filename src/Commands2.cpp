#include "Lib.hpp"
#include "Channel.hpp"
#include "Users.hpp"
#include "Replies.hpp"
#include "Server.hpp"


void	Server::Whois(Users *user, Command cmd){
	std::string name = cmd.Rest;
	Users *u = getUserByNn(name);
	for (std::vector<Users *>::iterator it = this->AllUsers.begin(); it != this->AllUsers.end(); it++){
		if ((*it)->getNickname() != name)
			user->setBuffer(ERR_NOSUCHNICK(this->getHost(), user->getNickname(), name));
		else
			user->setBuffer(RPL_WHOISUSER(this->getHost(), user->getNickname(), name, u->getUsername(), u->getHostname(), u->getRealname()));
			user->setBuffer(RPL_ENDOFWHOIS(this->getHost(), user->getNickname(), name));
	}
}