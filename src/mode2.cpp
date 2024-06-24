
#include "../include/Server.hpp"
#include "../include/Users.hpp"
#include "../include/Lib.hpp"
#include <cstring>

Users* CheckUser(std::vector<Users*>& allUsers, std::string& target) {
    for (std::vector<Users*>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it) {
        if ((*it)->getNickname() == target)
            return *it;
    }
    return NULL;
}


void setMode(std::string &currentModes, const std::string &modeString, const std::vector<std::string> &modeArgs) {
    // Simplified mode setting: only supports single character modes and no arguments
    for (std::string::const_iterator it = modeString.begin(); it != modeString.end(); ++it) {
        if (*it == '+') {
            ++it;
            while (it != modeString.end() && isalpha(*it)) {
                if (currentModes.find(*it) == std::string::npos) {
                    currentModes += *it;
                }
                ++it;
            }
        } else if (*it == '-') {
            ++it;
            while (it != modeString.end() && isalpha(*it)) {
                removeMode(currentModes, std::string(1, *it));
                ++it;
            }
        }
    }
}

void removeMode(std::string &currentModes, const std::string &modeString) {
    // Remove modes specified in modeString from currentModes
    for (std::string::const_iterator it = modeString.begin(); it != modeString.end(); ++it) {
        size_t pos = currentModes.find(*it);
        if (pos != std::string::npos) {
            currentModes.erase(pos, 1);
        }
    }
}

void c_mode(Command cmd, std::vector<Users *> AllUsers, std::vector<Channel *> AllChannels) {
    std::string target = cmd.params[0];
    std::string modeString = cmd.params[1];
    std::vector<std::string> param = cmd.params;

    if (target[0] == '#') { // Channel mode still in progress
        // if (std::find(AllChannels.begin(), AllChannels.end(), target) != AllChannels.end()) {
        //     std::cout << "Error " << "ERR_NOSUCHCHANNEL" << ": No such channel\n";
        //     return;
        // }

        // if (param.empty()) {
        //     std::cout << "Current modes for " << "target" << ": " << currentModes << "\n";
        // } else {
        //     setMode(currentModes, modeString, param);
        //     std::cout << "Updated modes for " << target << ": " << currentModes << "\n";
        // }
    } else { // User mode
        if (!CheckUser(AllUsers, target)) {
            std::cout << "Error " << "ERR_NOSUCHNICK" << ": No such nick\n";
            return;
        }

        Users *User = CheckUser(AllUsers, target);
        std::string currentModes = User->getMode();
        if (modeString.empty()) {
            std::cout << "Current modes for " << target << ": " << currentModes << "\n";
        } else {
            setMode(currentModes, modeString, param);
            std::cout << "Updated modes for " << target << ": " << currentModes << "\n";
        }
    }
}