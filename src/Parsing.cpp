#include "../include/Lib.hpp"
#include "../include/Replies.hpp"

int PortChecker(std::string Port)
{
	int p = 0;

	for (unsigned int i = 0;i < Port.length();i++)
	{
		if (!isdigit(Port[i]))
		{
			std::cerr << RED << "Please only enter digits as the Port!" << DEFAULT << std::endl;
			return 1;
		}
	}
	p = atoi(Port.c_str());
	if (p <= 6670 && p >= 6660)
		return 0;
	std::cerr << RED << "Please enter a valid Port!" << DEFAULT << std::endl;
	return 1;
}

bool	Check(std::string str, std::string find)
{
	if (str.empty() || find.empty())
		return false;
	if (str.rfind(find) == std::string::npos)
		return false;
	return true;
}

std::vector<std::string> MySplit(std::string str, std::string del)
{
	std::vector<std::string> tmp;

	if (!str.empty() && !del.empty())
	{
		int i = 0;
		while (str[i])
		{
		    int j = 0;
            i = str.find(del);
            if (i == -1)
                break ;
            else{

                tmp.push_back(str.substr(j, i));
                str = str.substr(i + del.length(), str.length());
                i = 0;
            }
		}
	}
    return tmp;
}

std::string	RCarriage(std::string str)
{
	std::string res;
	for (size_t i = 0;i < str.length();i++)
	{
		if (str[i] != '\r')
			res += str[i];
	}
	return res;
}

Command parse(std::string str)
{
	Command tmp;

	int i = 0;
	str = RSpaces(str);
	str = RCarriage(str);
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			tmp.CmdName = str.substr(0, i);
			break ;
		}
		i++;
	}
	if (tmp.CmdName.empty())
		tmp.CmdName = str.substr(0, str.length());
	if (tmp.CmdName.length() < str.length())
		tmp.Rest = str.substr(i + 1, str.length());
	tmp.Rest = RSpaces(tmp.Rest);
	return tmp;
}

std::vector<std::string> PrivSplit(std::string tmp)
{
	std::vector<std::string> res;
	std::string msg;
	std::string users;
	int i = 0;
	i = tmp.find(' ');
	msg = tmp.substr(i + 1, tmp.length() - i - 1);
	users = tmp.substr(0, i + 1);
	res.push_back(users);
	res.push_back(msg);
	return res;
}

int	OnlySpaces(std::string str)
{
	int i = 0;
	if (str.empty())
		return 1;
	while (str[i])
	{
		if (str[i] != ' ')
			return 0;
		i++;
	}
	return 1;
}

std::vector<std::string> KickSplit(std::string tmp)
{
	std::vector<std::string> res;
	std::string channel;
	std::string user;
	std::string	reason;
	int i = 0;
	i = tmp.find(' ');
	channel = tmp.substr(0, i);
	res.push_back(channel);
	tmp = tmp.substr(i + 1, tmp.length());
	tmp = RSpaces(tmp);
	if (tmp.find(' ') != std::string::npos)
	{
		i = tmp.find(' ');
		user = tmp.substr(0, i);
		if (OnlySpaces(user))
			return res;
		reason = tmp.substr(i + 1, tmp.length() - i);
		reason = RSpaces(reason);
		if (OnlySpaces(reason))
			return res;
		res.push_back(user);
		res.push_back(reason);
		return res;
	}
	user = tmp.substr(0, i + 1);
	if (OnlySpaces(user))
		return res;
	res.push_back(user);
	return res;
}

int	CheckMult(std::string str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '@' || str[i] == '#')
		{
			if (str[i + 1] && (str[i + 1] == '@' || str[i + 1] == '#'))
				return -1;
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '@' || str[i] == '#')
		{
			if (i == (int)strlen(str.c_str()) - 1)
				return -1;
		}
		i++;
	}
	return 0;
}

int	CheckPriv(Command &cmd)
{
	if (cmd.Rest.empty() || cmd.Rest.length() == 1)
		return -1;
	// if (cmd.Rest[0] != '@' && cmd.Rest[0] != '#')
	// 	return -1;
	// if (CheckMult(cmd.Rest) == -1)
	// 	return -1;
	if (cmd.Rest.find(' ') == std::string::npos)
		return -1;
	std::vector<std::string> tmp = PrivSplit(cmd.Rest);
	if (tmp.size() != 2)
		return -1;
	return 0;
}

int	CheckInv(Command &cmd)
{
	if (cmd.Rest.empty() || cmd.Rest.length() == 1)
		return -1;
	if (cmd.Rest.find(' ') == std::string::npos)
		return -1;
	std::vector<std::string> tmp = Split(cmd.Rest);
	if (tmp.size() != 2)
		return -1;
	return 0;
}

int	CheckJoin(Command &cmd)
{
	if (cmd.Rest.empty() || cmd.Rest.length() == 1)
		return -1;
	std::vector<std::string> tmp = Split(cmd.Rest);
	return 0;
}

int	CheckPart(Command &cmd)
{
	if (cmd.Rest.empty() || cmd.Rest.length() == 1)
		return -1;
	std::vector<std::string> tmp = Split(cmd.Rest);
	return 0;
}

int	CheckKick(Command &cmd)
{
	if (cmd.Rest.empty() || cmd.Rest.length() == 1)
		return -1;
	std::vector<std::string> tmp = KickSplit(cmd.Rest);
	if (tmp.size() < 2)
		return -1;
	if (tmp.size() == 3)
	{
		std::vector<std::string>::iterator it = tmp.end();
		it--;
		if ((*it).length() >= KICKLEN)
			return -1;
	}
	return 0;
}

int	CheckMode(Command &cmd)
{
	int i = 0;
	std::string channel;
	std::string mode;
	std::string arg;

	if (OnlySpaces(cmd.Rest))
		return -1;
	if (cmd.Rest.find(' ') == std::string::npos)
	{
		cmd.params.push_back(cmd.Rest);
		return 0;
	}
	i = cmd.Rest.find(' ');
	channel = cmd.Rest.substr(0, i);
	cmd.params.push_back(channel);
	cmd.Rest = cmd.Rest.substr(i + 1, cmd.Rest.length() - i);
	cmd.Rest = RSpaces(cmd.Rest);
	if (cmd.Rest.find(' ') == std::string::npos)
	{
		if (OnlySpaces(cmd.Rest))
			return 0;
		if (cmd.Rest.length() != 2)
			return -1;//RPL unk mode chr
		cmd.params.push_back(cmd.Rest);
		return 0;
	}
	i = cmd.Rest.find(' ');
	mode = cmd.Rest.substr(0, i);
	if (mode.length() != 2)
		return -1;//RPL unk mode chr
	cmd.params.push_back(mode);
	arg = cmd.Rest.substr(i + 1, cmd.Rest.length() -  i);
	arg = RSpaces(arg);
	if (OnlySpaces(arg))
		return 0;
	cmd.params.push_back(arg);
	return 0;
}

int	CheckCmd(Command &cmd, Users *user)
{
	if (cmd.CmdName == "CAP")
		return 0;
	if (cmd.CmdName == "PASS")
		return 0;
	if (cmd.CmdName == "NICK")
		return CheckNick(cmd, user);
	if (cmd.CmdName == "USER")
		return CheckUser(cmd, user);
	if (cmd.CmdName == "PRIVMSG")
		return CheckPriv(cmd);
	if (cmd.CmdName == "INVITE")
		return CheckInv(cmd);
	if (cmd.CmdName == "JOIN")
		return CheckJoin(cmd);
	if (cmd.CmdName == "PART")
		return CheckPart(cmd);
	if (cmd.CmdName == "QUIT")
		return 0;
	if (cmd.CmdName == "PING")
		return 0;
	if (cmd.CmdName == "KICK")
		return CheckKick(cmd);
	if (cmd.CmdName == "MODE")
		return CheckMode(cmd);
	if (cmd.CmdName == "TOPIC")
		return CheckTopic(cmd);
	else
		user->setBuffer(ERR_UNKNOWNCOMMAND(user->getHostname(), cmd.CmdName, user->getNickname()));
	return 0;
}

int	CheckTopic(Command &cmd)
{
	if (cmd.Rest.length() == 0)
		return -1;
	if (cmd.Rest.find(' ') == std::string::npos)
	{
		cmd.params.push_back(cmd.Rest);
		return 0;
	}
	int i = cmd.Rest.find(' ');
	std::string chan = cmd.Rest.substr(0, i);
	cmd.params.push_back(chan);
	std::string topic = cmd.Rest.substr(i + 1, cmd.Rest.length() - i);
	cmd.params.push_back(topic);
	return 0;
}

std::vector<std::string> Split(std::string str)
{
	std::vector<std::string> tmp;
	int i = 0;
	str = RSpaces(str);
	int j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != ' ')
			i++;
		tmp.push_back(str.substr(j, i - j));
		while (str[i] && str[i] == ' ')
			i++;
		j = i;
	}
	return tmp;
}

int	CheckUser(Command &cmd, Users *user)
{
	if (user->getStatus() < 2)
		return (ERR_NOTREGISTERED(user->getHostname()), -1);
	cmd.params = Split(cmd.Rest);
	if (cmd.params.size() != 4)
		return (user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName)),-1);
	std::vector<std::string>::iterator it = cmd.params.begin();
	if ((*it).length() > USERLEN)
		return (user->setBuffer(ERR_INPUTTOOLONG(user->getHostname())), -1);
	it++;
	if ((*it) != "0")
		return (user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName)),-1);
	it++;
	if ((*it) != "*")
		return (user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName)),-1);
	it++;
	if ((*it).length() <= 1)
		return (user->setBuffer(ERR_NEEDMOREPARAMS(user->getHostname(), cmd.CmdName)),-1);
	return 0;
}

std::string	RSpaces(std::string str)
{
	int i = 0;
	std::string res;

	res = str;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (i)
		res = str.substr(i, str.length() - i);
	i = 0;
	while (res[i])
		i++;
	i--;
	while (res[i] && (res[i] == ' ' || res[i] == '\t' || res[i] == '\n' || res[i] == '\r'))
		i--;
	res = res.substr(0, i + 1);
	return res;
}

int	CheckNick(Command &cmd, Users *user)
{
	if (user->getStatus() < 2)
		return (ERR_NOTREGISTERED(user->getHostname()), -1);
	if (cmd.Rest.empty())
		return (user->setBuffer(ERR_NONICKNAMEGIVEN(user->getHostname())), -1);
	int	i;
	if (cmd.Rest.length() > NICKLEN || cmd.Rest[0] == '#' || cmd.Rest[0] == '&' || cmd.Rest[0] == ':'
			 || cmd.Rest[0] == '@' || isdigit(cmd.Rest[0]) || std::isspace(cmd.Rest[0] || cmd.Rest.length() < 3))
		return ((user->setBuffer(ERR_ERRONEUSNICKNAME(user->getHostname(), cmd.Rest))),-1);
	i = 0;
	while (i < (int)strlen(cmd.Rest.c_str()))
	{
		if (!isalnum(cmd.Rest[i]) && cmd.Rest[i] != '\\' && cmd.Rest[i] != '|'
			&& cmd.Rest[i] != '[' && cmd.Rest[i] != ']' && cmd.Rest[i] != '{'
			&& cmd.Rest[i] != '}' && cmd.Rest[i] != '-' && cmd.Rest[i] != '_')
			return ((user->setBuffer(ERR_ERRONEUSNICKNAME(user->getHostname(), cmd.Rest))),-1);
		i++;
	}
	return 0;
}

