
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
