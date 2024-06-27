#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"
#include "../include/Replies.hpp"
#include <cstring>

std::vector<std::string> split(const std::string &str, const char *delimiter);

void Server::c_part(Command cmd, Users* user)
{
    if (cmd.params[0].empty())
        return(user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName)));
    std::string reason = cmd.params[1];
    std::vector<std::string> channels = split(cmd.params[0], ",");
    for (std::vector<std::string>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        Channel *channel = getChannel(*it);
        if (channel == NULL)
            return(user->setBuffer(ERR_NOSUCHCHANNEL(user->getHostname(), *it)));
        if (!channel->UserIsInC(user))
            return(user->setBuffer(ERR_NOTONCHANNEL(user->getHostname(), user->getNickname())));
        channel->deleteUserfromC(user);

    }
    // return(user->setBuffer(RPL_(user->getHostname(), user->getNickname())));

}