#include "../include/Channel.hpp"

Channel::Channel(std::string name){
	Name = name;
	Password = "random";
	Topic = "random";
	limit = -1;
	Mode = "-iltk";
}

Channel::Channel(const	Channel &cp){
	if (this != &cp){
		setName(cp.getName());
		setPassword(cp.getPassword());
		setTopic(cp.getTopic());
		setLimit(cp.getLimit());
	}
}

Channel	&Channel::operator=(const Channel &og){
	if (this != &og){
		setName(og.getName());
		setPassword(og.getPassword());
		setTopic(og.getTopic());
		setLimit(og.getLimit());
	}
	return (*this);
}

void	Channel::setName(std::string name){
	this->Name = name;
}
void	Channel::setPassword(std::string password){
	this->Password = password;
}
void	Channel::setTopic(std::string topic){
	this->Topic = topic;
}
void	Channel::setLimit(int limit){
	this->limit = limit;
}
void	Channel::setQuote(std::string Quote){
	this->Quote = Quote;
}
std::string	Channel::getName() const{
	return (this->Name);
}
std::string	Channel::getPassword() const{
	return (this->Password);
}
std::string	Channel::getTopic() const{
	return (this->Topic);
}
std::string Channel::getQuote() const{
	return (this->Quote);
}
int		Channel::getLimit() const{
	int	lim = this->limit;
	return (lim);
}

int		Channel::getinvitef() const{
	int	inf = this->invitef;
	return (inf);
}

void	Channel::addUsertoC(Users *user){
	for (std::vector<struct C_Users>::iterator it = this->UserList.begin(); it != this->UserList.end(); it++){
		if ((*it).nickName == user->getNickname()){
			return ;
		}
	}
	C_Users tmp;
	tmp.nickName = user->getNickname();
	tmp.flag = 0;
	this->UserList.push_back(tmp);
}

void	Channel::deleteUserfromC(Users *goner){
	for (std::vector<struct C_Users>::iterator it = this->UserList.begin(); it != this->UserList.end(); it++){
		if ((*it).nickName == goner->getNickname()){
			this->UserList.erase(it);
			return ;
		}
	}
}

void	Channel::fliptoOperator(Users	*user){
	std::string N = user->getNickname();
	for (std::vector<struct C_Users>::iterator it = this->UserList.begin(); it != this->UserList.end(); it++){
		if ((*it).nickName == N){
			if ((*it).flag == 1)
				(*it).flag = 0;
			else
				(*it).flag = 1;
		}
	}
}

void	Channel::CheckifOP(Users *user, Channel *channel){
	std::string N = user->getNickname();
	for (std::vector<struct C_Users>::iterator it = this->UserList.begin(); it != this->UserList.end(); it++){
		if ((*it).nickName == N){
			if ((*it).flag == 1)
				std::cout << N << " is an operator" << std::endl;
			else
				std::cout << N << " is not an operator" << std::endl;
		}
	}
	(void)channel;
}