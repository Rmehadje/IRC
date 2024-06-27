#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"
#include "../include/Replies.hpp"
#include <cstring>

std::vector<std::string> split(const std::string &str, const char *delimiter) {
    std::vector<std::string> tokens;
    char *cstr = new char[str.length() + 1];
    std::strcpy(cstr, str.c_str());

    char *token = std::strtok(cstr, delimiter);
    while (token != NULL) {
        tokens.push_back(std::string(token));
        token = std::strtok(NULL, delimiter);
    }

    delete[] cstr;
    return tokens;
}





//-----------------Quit Command------------------//



//----------------PRIVMSG Command------------//

// Channel* CheckChannel(const std::vector<Channel*>& allChannels, const std::string& target) {
//     for (std::vector<Channel*>::const_iterator it = allChannels.begin(); it != allChannels.end(); ++it) {
//         if ((*it)->getName() == target)
//             return *it;
//     }
//     return NULL; // Return NULL if the channel is not found
// }
// int CheckUser(const std::vector<Users*>& allUsers, const std::string& target) {
//     for (std::vector<Users*>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it) {
//         if ((*it)->getNickname() == target)
//             return (*it)->getSocket();
//     }
//     return 0;
// }

// bool isInChannel(const std::string& nickname, const std::vector<struct C_Users>& userList) {
//     for (std::vector<struct C_Users>::const_iterator it = userList.begin(); it != userList.end(); ++it) {
//         if (it->nickName == nickname && it->flag == 1) {
//             return true;
//         }
//     }
//     return false;
// }
// void c_privmsg(Command cmd, Users *user, std::vector<Users *> AllUsers, std::vector<Channel *> AllChannels){
//     Channel *isChannel;
//     int isUser;
//     if (cmd.params[0]== "")
//         return(user->setBuffer(ERR_NOTEXTTOSEND(user->getHostname(), user->getNickname())));
//     std::string param = cmd.params[1];
//     if (user->getStatus() < 2)
// 		return(user->setBuffer(ERR_NOTREGISTERED(user->getHostname())));
//     if (param.empty())
//         return(user->setBuffer(ERR_NOTEXTTOSEND(user->getHostname(), user->getNickname())));
//     std::vector<std::string> target = split(cmd.params[0], ",");
//     if (target.empty())
//         return(user->setBuffer(ERR_NORECIPIENT(user->getHostname())));
//     for (std::vector<std::string>::const_iterator it = target.begin(); it != target.end(); ++it){
//         isChannel = CheckChannel(AllChannels, *it);

//         if (isChannel)
//             {
//                 for (std::vector<Users *>::const_iterator it = AllUsers.begin(); it != AllUsers.end(); ++it) {
//                     if ((*it)->getSocket() != user->getSocket() && isInChannel((*it)->getNickname(), isChannel->UserList)) {
//                         send((*it)->getSocket(), param.c_str(), param.length(), 0);
//                     }
//                 }
//             }
//         isUser = CheckUser(AllUsers, *it);
//         if (isUser)
//             send(isUser, param.c_str(), param.length(), 0);
//         if (!isUser && !isChannel)
//             return(user->setBuffer(ERR_NORECIPIENT(user->getHostname())));

//         isChannel = NULL;
//         isUser = NULL;
//     }
// }

// //---------------MODE Command------------------//

// //check mode.cpp

// //----------------INVITE Command-----------------//

// Users* CheckUserin(std::vector<Users*>& allUsers, std::string& target) {
//     for (std::vector<Users*>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it) {
//         if ((*it)->getNickname() == target)
//             return *it;
//     }
//     return NULL;
// }

// void c_invite(Command cmd, Users *user, std::vector<Users*> AllUsers, std::vector<Channel*> AllChanel)
// {
//     std::string channel = cmd.params[1];
//     std::string target = cmd.params[0];

//     if (user->getStatus() < 2)
// 		return (user->setBuffer(ERR_NOTREGISTERED(user->getHostname())));
//     Channel *cnl = CheckChannel(AllChanel, channel);
//     if (!cnl)
//         return(user->setBuffer(ERR_NOSUCHCHANNEL(user->getHostname(), channel)));
//     if (!isInChannel(user->getNickname(), cnl->UserList))
//         return(user->setBuffer(ERR_NOSUCHCHANNEL(user->getHostname(), channel)));
//     if (cnl->getinvitef())
//         return(user->setBuffer(ERR_CHANOPRIVSNEEDED(user->getHostname(), channel)));
//         return;
//     if (isInChannel(target, cnl->UserList))
//                 return(user->setBuffer(ERR_USERONCHANNEL(user->getHostname(), target, channel)));
//     if (!user->getMode().find("i") && cnl->getMode().find("i"))
//                 return(user->setBuffer(ERR_CHANOPRIVSNEEDED(user->getHostname(), channel)));
//     Users *tar = CheckUserin(AllUsers, target);
//     cnl->addUsertoC(tar);
//     return(user->setBuffer(ERR_USERONCHANNEL(user->getHostname(), target, channel)));
// }

// ------------------- KICK Command -------------------//
// void	Server::c_kick(Command cmd, Users *user)
// {

//     std::string channel = cmd.params[0];
//     std::vector<std::string> target = getTargets(cmd.params[1], ",");

//     if (channel.empty())
//         return(user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName)));
//     Channel *cnl = getChannel(channel);
//     if (cnl == NULL)
//         return(user->setBuffer(ERR_NOSUCHCHANNEL(user->getHostname(), channel)));
//     // if (!cnl->UserIsInC(user))
//     //     return(user->setBuffer(ERR_NOTONCHANNEL(user->getHostname(), channel)));
//     // if (cnl->getKickf())
//     // {
//     //     if (!cnl->CheckifOP(user))
//     //         return(user->setBuffer(ERR_CHANOPRIVSNEEDED(user->getHostname(), channel)));
//     // }
//     // for (std::vector<std::string>::const_iterator it = target.begin(); it != target.end(); ++it) {
//     //     Users *tar = getUserByNn(*it);
//     //     if (!cnl->UserIsInC(tar))
//     //         return(user->setBuffer(ERR_USERNOTINCHANNEL(user->getHostname(),tar->getNickname(), channel)));
//     //     cnl->deleteUserfromC(tar);
//     // }   
// }
// added to add the shit