#include "../include/Server.hpp"

void	Server::AddPtoUser(Command cmd, Users *user){
	std::string pword = cmd.Rest;
	if (user->getStatus() == 1){
		if (!pword.empty() && pword == this->Password){
			user->setStatus(2);
		}
		else{
			std::cout << "rwordone" << std::endl;
		}
	}
	else{
		std::cout << "rwordtwo" << std::endl;
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
