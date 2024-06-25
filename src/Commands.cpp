#include "../include/Server.hpp"
#include "../include/Replies.hpp"

void	Server::AddPtoUser(Command cmd, Users *user){
	std::string pword = cmd.Rest;
	if (user->getStatus() == 0)
		return (user->setBuffer(ERR_NOTREGISTERED(user->getHostname())));
	if (user->getStatus() == 1){
		if (!pword.empty() && pword == this->Password){
			user->setStatus(2);
			user->setBuffer(RPL_PASS(user->getHostname()));
		}
		else if (pword.empty())
			user->setBuffer((user->getHostname(), cmd.CmdName));
		else {
			user->setBuffer(ERR_PASSWDMISMATCH(user->getHostname()));
		}
	}
	else if (user->getStatus() >= 2){
		user->setBuffer(ERR_ALREADYREGISTERED(user->getHostname()));
	}
}

void	Server::AddNicktoUser(Command cmd, Users *user){
	if (user->getStatus() < 2)
		return (user->setBuffer(ERR_NOTREGISTERED(user->getHostname())));
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
	if (cmd.CmdName == "CAP")
	{
		if (cmd.Rest == "LS")
		{
			if (user->getStatus() == 0)
				user->setStatus(1);
			user->setBuffer(RPL_CAP(user->getHostname()));
		}
	}
}

void	Server::RegisterUser(Command cmd, Users *user)
{
	if (user->getStatus() < 2)
		return (user->setBuffer(ERR_NOTREGISTERED(user->getHostname())));
	if (user->getStatus() >= 2)
	{
		std::vector<std::string>::iterator it = cmd.params.begin();
		std::string username = *it;
		it = cmd.params.end();
		it--;
		std::string realname = *it;
		user->setRealname(realname);
		user->setUsername(username);
		user->setBuffer(RPL_USER(user->getHostname(), user->getUsername()));
		if (user->getStatus() == 3 && user->getNickname() == "*")
			return ;
		user->setStatus(user->getStatus() + 1);
	}
	if (user->getStatus() == 4)
		return (user->setBuffer(RPL_WELCOME(this->getHost(), user->getUsername(), user->getHostname(), user->getNickname())));
	return ;
}

void	Server::SendPong(Command msg, Users *user)
{
	if (msg.Rest.empty())
		return user->setBuffer("");
	user->setBuffer(msg.Rest + "\r\n");
}

static Channel* CheckChannel(const std::vector<Channel*>& allChannels, const std::string& target) {
    for (std::vector<Channel*>::const_iterator it = allChannels.begin(); it != allChannels.end(); ++it) {
        if ((*it)->getName() == target)
            return *it;
    }
    return NULL;
}

static bool	isInChannel(std::string name, std::vector<struct C_Users> Users)
{
	for(std::vector<struct C_Users>::iterator it = Users.begin();it != Users.end();it++)
	{
		if (name == (*it).nickName)
			return true;
	}
	return false;
}

void c_topic(Command cmd, Users *user, std::vector<Channel*> AllChanels)
{
   std::string ChannelName = cmd.params[0];
   Channel *Channel= CheckChannel(AllChanels, ChannelName);
   if (Channel == NULL)
        return(user->setBuffer(ERR_NOSUCHCHANNEL(user->getHostname(), ChannelName)));
	if (!isInChannel(user->getNickname(), Channel->UserList))
		return(user->setBuffer(ERR_NOTONCHANNEL(user->getHostname(), Channel->getName())));
	if (cmd.params.size() == 1)
	{
		if (Channel->getTopic().empty())
			return user->setBuffer(RPL_NOTOPIC(user->getHostname(), Channel->getName()));
		return user->setBuffer(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic()));
	}
	else
	{
		if (!Channel->getTopicf())
		{
			Channel->setTopic(cmd.params[1]);
			return user->setBuffer(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic()));
		}
		else
		{
			if (!Channel->CheckifOP(user))
				return (user->setBuffer(ERR_CHANOPRIVSNEEDED(user->getHostname(), Channel->getName())));
			else
			{
				Channel->setTopic(cmd.params[1]);
				return (user->setBuffer(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic())));
			}
		}
	}
}
