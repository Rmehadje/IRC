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

class Users;
struct Command
{
	std::string Rest;
	std::string	CmdName;
};

int PortChecker(std::string port);
bool	Check(std::string str, std::string find);
std::vector<std::string> MySplit(std::string str, std::string del);
Command parse(std::string str);
void	CheckCmd(std::string Name, Users *user);