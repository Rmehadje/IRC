#include "../include/Channel.hpp"

Channel::Channel(std::string name){
	Name = name;
	Password = "random";
	Topic = "random";
	limit = -1;
	Mode = "-iltk";
	Limitf  = false;
	Topicf = false;
	Invitef = false;
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
void	Channel::setLimitf(bool limitf){
	this->Limitf = limitf;
}
void	Channel::setTopicf(bool topicf){
	this->Topicf = topicf;
}
void	Channel::setInvitef(bool	invitef){
	this->Invitef = invitef;
}
void	Channel::setPasswordf(bool passwordf){
	this->Passf = passwordf;
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

std::string Channel::getMode() const{
	return (this->Mode);
}

int		Channel::getLimit() const{
	int	lim = this->limit;
	return (lim);
}

bool	Channel::getLimitf() const
{
	return this->Limitf;
}

bool Channel::getInvitef() const
{
	return this->Invitef;
}

bool	Channel::getTopicf() const{
	return this->Topicf;
}
bool	Channel::getPasswordf() const{
	return this->Passf;
}

int	Channel::getNumberofUsers(std::vector<struct C_Users>	UserList){
	return UserList.size();
}

std::vector<Users *> Channel::getAllUsersInChan(std::vector<Users *> AllUsers)
{
	std::vector<Users *> InChan;
	for (std::vector<Users *>::iterator it = AllUsers.begin();it != AllUsers.end();it++)
	{
		for (std::vector<struct C_Users>::iterator t = UserList.begin();t != UserList.end();t++)
		{
			if ((*it)->getNickname() == t->nickName)
				InChan.push_back(*it);
		}
	}
	return InChan;
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

bool	Channel::CheckifOP(Users *user){
	std::string N = user->getNickname();
	for (std::vector<struct C_Users>::iterator it = this->UserList.begin(); it != this->UserList.end(); it++){
		if ((*it).nickName == N){
			if ((*it).flag == 1)
				return true;
		}
	}
	return false;
}

void	Channel::brodcastMsg(std::string msg, std::vector<Users *> users)
{
	std::vector<Users *> InChan = getAllUsersInChan(users);
	for (std::vector<Users *>::iterator it = InChan.begin();it != InChan.end();it++)
		(*it)->setBuffer(msg);
}