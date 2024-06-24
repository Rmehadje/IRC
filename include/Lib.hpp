#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib> 
#include <cerrno> 
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include "Users.hpp"

#define RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define ORANGE "\033[38;5;202m\033[22m"
#define GRAY "\033[1;30m"
#define DEFAULT "\033[1;39m"
#define NICKLEN 30
#define USERLEN 18
#define KICKLEN 255
class Users;
struct Command
{
	std::string	CmdName;
	std::string	Rest;
	std::vector<std::string> params;
};

int PortChecker(std::string port);
bool	Check(std::string str, std::string find);
std::vector<std::string> MySplit(std::string str, std::string del);
Command parse(std::string str);
int	CheckCmd(Command &cmd, Users *user);
std::string	RSpaces(std::string str);
std::string	RCarriage(std::string str);
int	CheckNick(Command &cmd, Users *user);
int	CheckUser(Command &cmd, Users *user);
int	CheckPriv(Command &cmd);
int	CheckInv(Command &cmd);
int	CheckJoin(Command &cmd);
int	CheckPart(Command &cmd);
int	CheckKick(Command &cmd);
int	CheckMult(std::string str);
int	OnlySpaces(std::string str);
int	CheckTopic(Command &cmd);
int	CheckMode(Command &cmd);
std::vector<std::string> KickSplit(std::string tmp);
std::vector<std::string> PrivSplit(std::string tmp);
std::vector<std::string> Split(std::string str);