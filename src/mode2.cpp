
#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"
#include "../include/Replies.hpp"
#include <cstring>

Channel* CheckChannel(const std::vector<Channel*>& allChannels, const std::string& target) {
    for (std::vector<Channel*>::const_iterator it = allChannels.begin(); it != allChannels.end(); ++it) {
        if ((*it)->getName() == target)
            return *it;
    }
    return NULL;
}
Users* CheckUser(std::vector<Users*>& allUsers, std::string& target) {
    for (std::vector<Users*>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it) {
        if ((*it)->getNickname() == target)
            return *it;
    }
    return NULL;
}

// void removeMode(std::string &currentModes, const std::string &modeString) {
//     // Remove modes specified in modeString from currentModes
//     for (std::string::const_iterator it = modeString.begin(); it != modeString.end(); ++it) {
//         size_t pos = currentModes.find(*it);
//         if (pos != std::string::npos) {
//             currentModes.erase(pos, 1);
//         }
//     }
// }

void setMode(std::string &currentModes, const std::string &modeString, const std::vector<std::string> &modeArgs) {
    // Simplified mode setting: only supports single character modes and no arguments
    
    int i = 0;
    int j = 0;
    std::string pos = "";
    std::string neg = "";
    while (currentModes[i])
    {
        if (currentModes[i] == '+')
        {
            while(currentModes[++i] != '-' || currentModes[i] != NULL)
                pos+= currentModes[j];
        }
        if (currentModes[i] == '-')
        {
            while(currentModes[++i] != '+' || currentModes[i] != NULL)
                neg+= currentModes[j];
        }

    }
    for (std::string::const_iterator it = modeString.begin(); it != modeString.end(); ++it) {
        if (*it == '+') {
            ++it;
            while (it != modeString.end() && isalpha(*it)) {
                if (pos.find(*it) == std::string::npos) {
                    if (pos.find("+") == std::string::npos)
                        pos+="+";
                    while(*it != '+' && *it != '-')
                        {
                            pos += *it;
                            ++it;
                            }
                }
                ++it;
            }
        } else if (*it == '-') {
            ++it;
            while (it != modeString.end() && isalpha(*it)) {
                if (neg.find(*it) == std::string::npos) {
                    if (neg.find("-") == std::string::npos)
                        neg+="-";
                    while(*it != '+' && *it != '-')
                        {
                            neg += *it;
                            ++it;
                            }
                ++it;
            }
            }
        }
    }
    currentModes = pos + neg;
}


void Server::c_mode(Command cmd, Users *user) 
{
    std::string target = cmd.params[0];
    Channel *channel = getChannel(target);
    if (channel == NULL)
        return(user->setBuffer(ERR_NOSUCHCHANNEL(this->getHost(), target)));
    if (cmd.params.size() == 1)
    {
        return (user->setBuffer(RPL_CHANNELMODEIS(this->getHost(), channel->getName(), user->getNickname(), channel->getMode())));
    }
    std::string modeString = cmd.params[1];
    std::string currentModes = channel->getMode();
    if (!channel->CheckifOP(user))
        return (user->setBuffer(ERR_NOPRIVILIGES(this->getHost())));
    switch (modeString[1])
    {
        case 'i':
            if (modeString[0] == '-')
                channel->setInvitef(false);
            else
                channel->setInvitef(true);
            break;
        case 't':
            if (modeString[0] == '-')
                channel->setTopicf(false);
            else
                channel->setTopicf(true);
            break;
        case 'l':
            if (modeString[0] == '-')
                channel->setLimitf(false);
            else
            {
                if (cmd.params.size() != 3)
                    return (user->setBuffer(ERR_NEEDMOREPARAMS(this->getHost(), "MODE")));
                if (!IfNumbers(cmd.params[3]))
                    return (user->setBuffer(ERR_NEEDMOREPARAMS(this->getHost(), "MODE")));
                channel->setLimitf(true);
                channel->setLimit(std::atoi(cmd.params[3].c_str()));
            }
            break;
        case 'k':
            if (modeString[0] == '-')
                channel->setPasswordf(false);
            else
            {
                if (cmd.params.size() != 3)
                    return (user->setBuffer(ERR_NEEDMOREPARAMS(this->getHost(), "MODE")));
                if (!IfValid(cmd.params[3]))
                    return (user->setBuffer(ERR_NEEDMOREPARAMS(this->getHost(), "MODE")));
                channel->setPasswordf(true);
                channel->setPassword(cmd.params[3]);
            }
            break;
        case 'o':
            if (cmd.params.size() != 3)
                return (user->setBuffer(ERR_NEEDMOREPARAMS(this->getHost(), "MODE")));
            if (getUserByNn(cmd.params[3]) == NULL)
                return (user->setBuffer(ERR_NOSUCHNICK(this->getHost(), user->getNickname(), channel->getName())));
            if (!channel->UserIsInC(getUserByNn(cmd.params[3])))
                return (user->setBuffer(ERR_USERNOTINCHANNEL(this->getHost(), user->getNickname(), channel->getName())));
            if (modeString[0] == '-')
            {
                if (!channel->CheckifOP(getUserByNn(cmd.params[3])))
                    return (user->setBuffer(ERR_CHANOPRIVSNEEDED(this->getHost(), channel->getName())));
                channel->fliptoOperator(getUserByNn(cmd.params[3]));
                getUserByNn(cmd.params[3])->setBuffer(RPL_NOTOPERATORANYMORE(this->getHost(), channel->getName()));
            }
            else
            {
                if (channel->CheckifOP(getUserByNn(cmd.params[3])))
                    return (user->setBuffer(ERR_ALREADYOPERATOR(this->getHost(), user->getNickname(), channel->getName(), cmd.params[3])));
                channel->fliptoOperator(getUserByNn(cmd.params[3]));
                getUserByNn(cmd.params[3])->setBuffer(RPL_BECOMINGOPERATOR(this->getHost(), channel->getName()));
            }
            break;
        default:
            user->setBuffer(ERR_UNKNOWNMODE(this->getHost(), modeString));
            break;
    }
    channel->ChangeMode();
    channel->brodcastMsg(RPL_CHANNELMODEIS(this->getHost(), channel->getName(), user->getNickname(), channel->getMode()), AllUsers);
}