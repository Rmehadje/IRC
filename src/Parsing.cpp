#include "../include/Lib.hpp"

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

int	CheckCmd(Command cmd)
{
	if (cmd.CmdName == "CAP")
		return 0;
	if (cmd.CmdName == "PASS")
		return 0;
	if (cmd.CmdName == "NICK")
		return CheckNick(cmd);
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

int	CheckNick(Command cmd)
{
	if (cmd.Rest.empty())
		return -1;
	int	i;
	if (cmd.Rest.empty() || cmd.Rest.length() > 30 || cmd.Rest[0] == '#' || cmd.Rest[0] == '&' || cmd.Rest[0] == ':'
			 || cmd.Rest[0] == '@' || isdigit(cmd.Rest[0]) || std::isspace(cmd.Rest[0]))
		return -1;
	i = 0;
	while (i < (int)strlen(cmd.Rest.c_str()))
	{
		if (!isalnum(cmd.Rest[i]) && cmd.Rest[i] != '\\' && cmd.Rest[i] != '|'
			&& cmd.Rest[i] != '[' && cmd.Rest[i] != ']' && cmd.Rest[i] != '{'
			&& cmd.Rest[i] != '}' && cmd.Rest[i] != '-' && cmd.Rest[i] != '_')
			return -1;
		i++;
	}
	if (cmd.Rest.length() > 20 || cmd.Rest.length() < 4)
		return -1;
	return 0;
}

