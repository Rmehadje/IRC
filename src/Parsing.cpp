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

Command parse(std::string str)
{
	Command tmp;

	int i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	int j = i;
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			tmp.CmdName = str.substr(j, i - j);
			break ;
		}
		i++;
	}
	if (tmp.CmdName.empty())
		tmp.CmdName = str.substr(j, str.length() - j);
	if (tmp.CmdName.length() + j < str.length())
		tmp.Rest = str.substr(i + 1, str.length());
	return tmp;
}

void	CheckCmd(Command cmd, Users *user)
{
	if (cmd.CmdName == "PASS")
		CheckPass(cmd.Rest);
}

void	CheckPass(std::string pass)
{
	int i = 0;
	while (pass[i])
	{
		if (!isalnum(pass[i]))
			return ;
		i++;
	}
}