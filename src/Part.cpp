#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"
#include "../include/Replies.hpp"
#include <cstring>

std::vector<std::string> split(const std::string &str, const char *delimiter);

void Server::c_part(Command cmd, Users* user)
{
    if (cmd.params[0].empty())
        return(user->setBuffer(ERR_NEEDMOREPARAMS(this->getHost(), cmd.CmdName)));
    std::string reason = cmd.params[1];
    std::vector<std::string> channels = split(cmd.params[0], ",");
    for (std::vector<std::string>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        Channel *channel = getChannel(*it);
        if (channel == NULL){
            user->setBuffer(ERR_NOSUCHCHANNEL(this->getHost(), *it));
            continue ;
        }
        if (!channel->UserIsInC(user)){
            user->setBuffer(ERR_NOTONCHANNEL(this->getHost(), user->getNickname()));
            continue ;
        }
        channel->deleteUserfromC(user);
    user->setBuffer(RPL_PART(user->getSrc(), *it, ));

    }

}