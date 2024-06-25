#include "../include/Server.hpp"
#include "../include/Replies.hpp"

Server::Server(){}

Server::Server(int port, std::string password)
{
	Port = port;
	Password = password;
	this->setStatus(true);
	std::cout << GREEN << "-------STARTING---SERVER-------" << DEFAULT << std::endl;
}

Server::~Server(){}

Server::Server(const Server &cp)
{
	*this = cp;
}

Server &Server::operator=(const Server &cp)
{
	if (this != &cp)
		*this = cp;
	return *this;
}

void Server::setHost(std::string name)
{
	Host = name;
}

std::string Server::getHost() const
{
	return this->Host;
}

bool	Server::getStatus() const
{
	return ServerStatus;
}

void	Server::setStatus(bool flag)
{
	ServerStatus = flag;
}

int	Server::getPort() const
{
	return this->Port;
}

void	Server::addPfds(struct pollfd sfd) 
{
	this->Fds.push_back(sfd);
}

void	Server::setBytesReceived(int BytesReceived)
{
	this->BytesReceived = BytesReceived;
}

ssize_t Server::getBytesReceived()
{
	return this->BytesReceived;
}

Users *Server::getUserByFd(int fd) {
	for (std::vector<Users *>::iterator it = this->AllUsers.begin(); 
			it != this->AllUsers.end(); ++it) {
		if ((*it)->getSocket() == fd)
			return *it;
	}
	return NULL;
}


void	Server::removePfds(struct pollfd sfd)
{
	for (std::vector<struct pollfd>::iterator it = this->Fds.begin(); it != this->Fds.end(); ++it) {
		if ((*it).fd == sfd.fd && ((*it).events == sfd.events)) {
			this->Fds.erase(it);
			return ;
		}
	}
}

void  Server::addUser(Users *user)
{
  this->AllUsers.push_back(user);
}

void	Server::removeUserFromServer(Users *user)
{
	for (std::vector<pollfd>::iterator it = this->Fds.begin(); it != this->Fds.end(); it++)
	{
		if ((*it).fd == this->ServerSocket)
			continue ;
		if ((*it).fd == user->getSocket()) 
		{
			this->Fds.erase(it);
			break ;
		}
	}
	for (std::vector<Users *>::iterator it = this->AllUsers.begin(); it != this->AllUsers.end(); ++it) {
		if ((*it) == user) 
		{
			this->AllUsers.erase(it);
			break ;
		}
	}
	delete user;
}

void Server::handleMsg(Users *user)
{
	setBytesReceived(recv(user->getSocket(), this->buffer, sizeof(this->buffer), 0));
	if (getBytesReceived() <= 0) {
		if (getBytesReceived() == 0)
			std::cout << "Connection closed." << std::endl;
		else
			std::cerr << "Error: recv: " << strerror(errno) << std::endl;
		removeUserFromServer(user);
	}
	else {
		std::string msg(buffer, getBytesReceived());
		std::memset(this->buffer, '\0', sizeof(this->buffer));
		user->setCmd(msg);
		if (!Check(user->getCmd(), "\r\n"))
			return ;
		std::vector<std::string> vec = MySplit(user->getCmd(), "\r\n");
		std::string tmp = user->getCmd().substr(user->getCmd().rfind("\r\n") + 2);
		user->clearCmd();
		user->setCmd(tmp);
		for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it) {
			Command cmd = parse(*it);
			std::cout <<"Recv"<< *it << std::endl;
			if (!CheckCmd(cmd, user))
				executeCmd(cmd, user);
		}
	}
}

void Server::executeCmd(Command msg, Users *user)
{
	std::cout << user->getStatus() << std::endl;
	if (user->getStatus() != 4 && (msg.CmdName != "PING" && msg.CmdName != "CAP" && msg.CmdName != "NICK" && msg.CmdName != "USER" && msg.CmdName != "PASS"))
		return user->setBuffer(ERR_NOTREGISTERED(getHost()));
	// std::cout << YELLOW << msg.CmdName << DEFAULT << std::endl;
	if (msg.CmdName == "CAP")
		CapInit(msg, user);
	else if (msg.CmdName == "PASS")
			AddPtoUser(msg, user);
	else if (msg.CmdName == "NICK")
			AddNicktoUser(msg, user);
	else if (msg.CmdName == "USER")
			RegisterUser(msg, user);
	else if (msg.CmdName == "PING")
			SendPong(msg, user);
	else if (msg.CmdName == "QUIT")
		c_quit(msg ,user);
	else if (msg.CmdName == "JOIN")
		std::cout << "GOOD" << std::endl;
    	// c_join(msg.parameters, user);
	else if (msg.CmdName == "PART")
		std::cout << "GOOD" << std::endl;
		// c_part(msg.parameters, user);
	else if (msg.CmdName == "KICK")
		std::cout << "GOOD" << std::endl;
    	// c_kick(msg.parameters, user);
  	else if (msg.CmdName == "INVITE")
		std::cout << "GOOD" << std::endl;
    	// c_invite(msg.parameters, user);
	else if (msg.CmdName == "TOPIC")
		std::cout << "GOOD" << std::endl;
		// c_topic(msg.parameters,user, AllChanels)
    	// c_topic(msg.parameters, user);
	else if (msg.CmdName == "MODE")
		std::cout << "GOOD" << std::endl;
		// c_mode(msg.parameters, user);
		// c_mode(msg.parameters, AllUsers, AllChannels)
	else if (msg.CmdName == "PRIVMSG")
		std::cout << "GOOD" << std::endl;
		// c_privmsg(msg.parameters, user);
		// c_privmsg(cmd, user, AllUsers, AllChannels)
		// c_quit(msg.parameters, user);
}
