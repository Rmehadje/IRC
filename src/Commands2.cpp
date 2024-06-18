#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"

void broadcast_quit_message(Users user, const std::string& message, std::vector<Users *> AllUsers) {
    for (std::vector<Users *>::const_iterator it = AllUsers.begin(); it != AllUsers.end(); ++it) {
        if ((*it)->getSocket() != user.getSocket()) {
            send((*it)->getSocket(), message.c_str(), message.length(), 0);
        }
    }
}

void c_quit(std::string param, Users user, std::vector<Users *>	AllUsers){
    std::string message =  user.getNickname() + "is exiting network with the message: \"" + param + "\" \r\n";
    broadcast_quit_message(user, message, AllUsers);
    close(user.getSocket());
}

