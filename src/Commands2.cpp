#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"
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


void broadcast_quit_message(Users user, const std::string& message, std::vector<Users *> AllUsers) {
    for (std::vector<Users *>::const_iterator it = AllUsers.begin(); it != AllUsers.end(); ++it) {
        if ((*it)->getSocket() != user.getSocket()) {
            send((*it)->getSocket(), message.c_str(), message.length(), 0);
        }
    }
}

void c_quit(Command cmd, Users user, std::vector<Users *>	AllUsers){
    std::string param = cmd.Rest;
    std::string message =  user.getNickname() + "is exiting network with the message: \"" + param + "\" \r\n";
    broadcast_quit_message(user, message, AllUsers);
    close(user.getSocket());
}

//----------------PRIVMSG Command------------//

Channel* CheckChannel(const std::vector<Channel*>& allChannels, const std::string& target) {
    for (std::vector<Channel*>::const_iterator it = allChannels.begin(); it != allChannels.end(); ++it) {
        if ((*it)->getName() == target)
            return *it;
    }
    return NULL; // Return NULL if the channel is not found
}
int CheckUser(const std::vector<Users*>& allUsers, const std::string& target) {
    for (std::vector<Users*>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it) {
        if ((*it)->getNickname() == target)
            return (*it)->getSocket();
    }
    return 0;
}

bool isInChannel(const std::string& nickname, const std::vector<struct C_Users>& userList) {
    for (std::vector<struct C_Users>::const_iterator it = userList.begin(); it != userList.end(); ++it) {
        if (it->nickName == nickname && it->flag == 1) {
            return true;
        }
    }
    return false;
}
void c_privmsg(Command cmd, Users user, std::vector<Users *> AllUsers, std::vector<Channel *> AllChannels){
    Channel *isChannel;
    int isUser;
    std::string param = cmd.params[1];
    std::vector<std::string> target = split(cmd.params[0], ",");
    for (std::vector<std::string>::const_iterator it = target.begin(); it != target.end(); ++it){
        isChannel = CheckChannel(AllChannels, *it);
        isUser = CheckUser(AllUsers, *it);

        if (isChannel)
            {
                for (std::vector<Users *>::const_iterator it = AllUsers.begin(); it != AllUsers.end(); ++it) {
                    if ((*it)->getSocket() != user.getSocket() && isInChannel((*it)->getNickname(), isChannel->UserList)) {
                        send((*it)->getSocket(), param.c_str(), param.length(), 0);
                    }
                }
            }
        if (isUser)
            send(isUser, param.c_str(), param.length(), 0);
    //else
        //error handeling with code number thingy 
        isChannel = NULL;
        isUser = NULL;
    }
}

//---------------MODE Command------------------//

//check mode.cpp

// -------------TOPIC Command------------------//

void c_topic(Command cmd, Users user, std::vector<Channel*> AllChanels)
{
    std::string ChannelName;
    if (cmd.params[1] != "")
        ChannelName = cmd.params[1];
    else{
        // code thingy
        return;
    }
    Channel *Channel= CheckChannel(AllChanels, ChannelName);
    if (Channel = NULL)
    {
        //code thingy
        return;
    }
    Channel->setTopic(cmd.params[0]);
}

//----------------INVITE Command-----------------//

Users* CheckUserin(std::vector<Users*>& allUsers, std::string& target) {
    for (std::vector<Users*>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it) {
        if ((*it)->getNickname() == target)
            return *it;
    }
    return NULL;
}

void c_invite(Command cmd, Users user, std::vector<Users*> AllUsers, std::vector<Channel*> AllChanel)
{
    std::string channel = cmd.params[1];
    std::string target = cmd.params[0];

    Channel *cnl = CheckChannel(AllChanel, channel);
    if (!cnl)
        // return(ERR_NOSUCHCHANNEL);
        return;
    if (!isInChannel(user.getNickname(), cnl->UserList))
        // return("RR_NOTONCHANNEL");
        return;
    if (cnl->getinvitef())
        // return(ERR_CHANOPRIVSNEEDED);
        return;
    if (isInChannel(target, cnl->UserList))
        // return(ERR_USERONCHANNEL);
        return;
    Users *tar = CheckUserin(AllUsers, target);
    cnl->addUsertoC(tar);
    std::string msg = user.getNickname() + " has invited you to " + channel;
    send(tar->getSocket(), msg.c_str(), msg.length(), 0);

}