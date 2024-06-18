#include "../include/Server.hpp"

void	Server::AddPtoUser(Command cmd, Users *user){
	std::string pword = user->getPassword();
	if (pword.empty() || user->getNickname() == "*"){
		user->setPassword(cmd.Rest);
	}
	else{
		std::cout << "YOU CANT CHANGE PASS BOZO" << std::endl;
	}
}

void	Server::AddNicktoUser(Command cmd, Users *user){
	std::string Nick = cmd.Rest;
	for (std::vector<Users *>::iterator it = this->AllUsers.begin(); it != this->AllUsers.end(); it++){
			if ((*it)->getNickname() == Nick){
				std::cout << "this Nickname already exists, please chose a different one" << std::endl;
			}
	}
	user->setNickname(cmd.Rest);
}

