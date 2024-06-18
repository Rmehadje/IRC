#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"

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
void c_privmsg(Command cmd, Users user, std::string target, std::vector<Users *>	AllUsers, std::vector<Channel *> AllChannels){

    std::string param = cmd.Rest;
    Channel *isChannel = CheckChannel(AllChannels, target);
    int isUser = CheckUser(AllUsers, target);

    if (isChannel)
    {
        for (std::vector<Users *>::const_iterator it = AllUsers.begin(); it != AllUsers.end(); ++it) {
            if ((*it)->getSocket() != user.getSocket() && isInChannel((*it)->getNickname(), isChannel->UserList)) {
                send((*it)->getSocket(), param.c_str(), param.length(), 0);
        }
    }
    }
    else if (isUser)
        send(isUser, param.c_str(), param.length(), 0);
    //else
        //error handeling with code number thingy 
}

//---------------MODE Command------------------//

