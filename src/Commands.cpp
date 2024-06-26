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
	if (user->getStatus() == 4 && user->getNickname() != "*")
	{
		std::string Nick = cmd.Rest;
		for (std::vector<Users *>::iterator it = this->AllUsers.begin(); it != this->AllUsers.end(); it++){
				if ((*it)->getNickname() == Nick){
					user->setBuffer(ERR_NICKNAMEINUSE(user->getHostname(), Nick));
					return ;
				}
		}
		user->setBuffer(RPL_NICKCHANGE(user->getNickname(), user->getUsername(), user->getHostname(), cmd.Rest));
		return user->setNickname(cmd.Rest);
	}
	if (user->getStatus() >= 2 && user->getStatus() < 4)
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
	if (user->getStatus() == 4 && user->getUsername() != "*")
		return user->setBuffer(ERR_ALREADYREGISTERED(this->getHost()));
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

// static Channel* CheckChannel(const std::vector<Channel*>& allChannels, const std::string& target) {
//     for (std::vector<Channel*>::const_iterator it = allChannels.begin(); it != allChannels.end(); ++it) {
//         if ((*it)->getName() == target)
//             return *it;
//     }
//     return NULL;
// }

static bool	isInChannel(std::string name, std::vector<struct C_Users> Users)
{
	for(std::vector<struct C_Users>::iterator it = Users.begin();it != Users.end();it++)
	{
		if (name == (*it).nickName)
			return true;
	}
	return false;
}

// void Server::c_topic(Command cmd, Users *user)
// {
//    std::string ChannelName = cmd.params[0];
//    Channel *Channel= CheckChannel(AllChannels, ChannelName);
//    if (Channel == NULL)
//         return(user->setBuffer(ERR_NOSUCHCHANNEL(user->getHostname(), ChannelName)));
// 	if (!isInChannel(user->getNickname(), Channel->UserList))
// 		return(user->setBuffer(ERR_NOTONCHANNEL(user->getHostname(), Channel->getName())));
// 	if (cmd.params.size() == 1)
// 	{
// 		if (Channel->getTopic().empty())
// 			return user->setBuffer(RPL_NOTOPIC(user->getHostname(), Channel->getName()));
// 		return user->setBuffer(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic()));
// 	}
// 	else
// 	{
// 		if (!Channel->getTopicf())
// 		{
// 			Channel->setTopic(cmd.params[1]);
// 			return Channel->brodcastMsg(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic()), AllUsers);
// 			// return user->setBuffer(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic()));
// 		}
// 		else
// 		{
// 			if (!Channel->CheckifOP(user))
// 				return (user->setBuffer(ERR_CHANOPRIVSNEEDED(user->getHostname(), Channel->getName())));
// 			else
// 			{
// 				Channel->setTopic(cmd.params[1]);
// 				return Channel->brodcastMsg(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic()), AllUsers);
// 				// return (user->setBuffer(RPL_TOPIC(user->getHostname(), Channel->getName(), Channel->getTopic())));
// 			}
// 		}
// 	}
// }


std::vector<std::string> getTargets(std::string targets)
{
	std::vector<std::string> res;
	std::string tmp;
	if (targets.find(',') == std::string::npos)
		return (res.push_back(RSpaces(targets)), res);
	int i = 0;
	while (targets[i])
	{
		int j = 0;
		if (targets.find(',') != std::string::npos)
		{
			i = targets.find(',');
			tmp = targets.substr(j, i);
			if (!tmp.empty())
				res.push_back(tmp);
			targets = targets.substr(i + 1, targets.length() - i + 1);
			targets = RSpaces(targets);
		}
		else
		{
			targets = RSpaces(targets);
			res.push_back(targets);
			break ;
		}
	}
	return res;
}

void	Server::c_privmsg(Command cmd, Users *user)
{
	std::vector<std::string> targets = getTargets(cmd.params[0]);
	if (targets.size() == 0)
		return ;
	for (std::vector<std::string>::iterator it = targets.begin();it != targets.end();it++)
	{
		if (OnlySpaces(*it))
		{
			user->setBuffer(ERR_NOSUCHNICK(user->getHostname(), user->getNickname(), *it));
			continue;
		}
		if ((*it)[0] == '#')
		{
			if (getChannel(*it) == NULL)
			{
				user->setBuffer(ERR_NOSUCHCHANNEL(user->getHostname(), *it));
				continue;
			}
			if (!isInChannel(user->getNickname(), getChannel(*it)->UserList))
			{
				user->setBuffer(ERR_NOTONCHANNEL(user->getHostname(), *it));
				continue;
			}
			getChannel(*it)->brodcastMsg(cmd.params[1], AllUsers);
		}
		else
		{
			if (!getUserByNn(*it))
			{
				user->setBuffer(ERR_NOSUCHNICK(user->getHostname(), user->getNickname(), *it));
				continue;
			}
			getUserByNn(*it)->setBuffer(RPL_PRIVMSG(user->getNickname(), user->getUsername(), user->getHostname(), *it, cmd.params[1]));
		}
	}
}

void	Server::join(Command cmd, Users *user)
{
	std::vector<std::string> chan_name = getTargets(cmd.params[0]);
	std::vector<std::string> key_lst;
	if (cmd.params.size() == 2)
		key_lst = getTargets(cmd.params[1]);
	for (std::vector<std::string>::iterator it = chan_name.begin(); it != chan_name.end(); ++it) {
		Channel *chan = getChannel(*it);
		if (!chan) {
			//check channel name
			chan = new Channel(*it);
			this->AddChanToServ(chan);
			chan->addUsertoC(user);
			chan->fliptoOperator(user);
			if (!key_lst.empty()) {
				std::string key = *(key_lst.begin());
				key_lst.erase(key_lst.begin());
				chan->setPassword(key);
				chan->setPasswordf(true);
			}
			user->setBuffer(RPL_JOIN(user->getNickname(), user->getUsername(), user->getHostname(), chan->getName()));
		}
		else {
			if (chan->getLimitf())
			{
				if (chan->getLimit() >= chan->getNumberofUsers())
				{
					user->setBuffer(ERR_CHANNELISFULL(user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname(), chan->getName()));
					continue;
				}
			}
			if (chan->getInvitef())
			{
				user->setBuffer(ERR_INVITEONLYCHAN(user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname(), chan->getName()));
				continue;
			}
			if (chan->getPasswordf()) {
				if (!key_lst.empty())
				{
					std::string key = *(key_lst.begin());
					key_lst.erase(key_lst.begin());
					if (chan->getPassword() == key) {
						chan->brodcastMsg(RPL_JOIN(user->getNickname(), user->getUsername(), user->getHostname(), chan->getName()), AllUsers);
						chan->addUsertoC(user);
						chan->brodcastMsg(RPL_BOT_CWELCOME(user->getNickname(), chan->getName()), AllUsers);
						if (chan->getTopic().empty())
							user->setBuffer(RPL_NOTOPIC(this->getHost(), user->getNickname(), chan->getName()));
						else
							user->setBuffer(RPL_TOPIC(this->getHost(), user->getNickname(), chan->getName(), chan->getTopic()));
						user->setBuffer(RPL_NAMERPLY(this->getHost(), user->getNickname(), chan->getName(), chan->getAllUsersInChanList(AllUsers)));
						user->setBuffer(RPL_ENDOFNAMES(this->getHost(), user->getNickname(), chan->getName()));
					}
					else
						user->setBuffer(ERR_BADCHANNELKEY(user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname(), chan->getName()));
				}
				else
					user->setBuffer(ERR_BADCHANNELKEY(user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname(), chan->getName())); 
			}
			else {
				chan->brodcastMsg(RPL_JOIN(user->getNickname(), user->getUsername(), user->getHostname(), chan->getName()), AllUsers);
				chan->addUsertoC(user);
				chan->brodcastMsg(RPL_BOT_CWELCOME(user->getNickname(), chan->getName()), AllUsers);
				if (chan->getTopic().empty())
					user->setBuffer(RPL_NOTOPIC(this->getHost(), user->getNickname(), chan->getName()));
				else
					user->setBuffer(RPL_TOPIC(this->getHost(), user->getNickname(), chan->getName(), chan->getTopic()));
				user->setBuffer(RPL_NAMERPLY(this->getHost(), user->getNickname(), chan->getName(), chan->getAllUsersInChanList(AllUsers)));
				user->setBuffer(RPL_ENDOFNAMES(this->getHost(), user->getNickname(), chan->getName()));

			}

			}
		}	

	}