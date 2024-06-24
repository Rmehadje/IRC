#pragma once

//error replies

#define RPL_WELCOME(src, user, host, nick)				":" + src + " 001 " + "Welcome to the IRC_server network " nick "." + user + "@" + host + "\r\n"
#define RPL_UMODEIS(src, nick, mode)						":" + src + " 221 " + nick + " " + mode + "\r\n"
#define RPL_LUSERUNKNOWN()
#define ERR_NOSUCHNICK(src, nick, chan)					":" + src + " 401 " + nick + " " + chan + " :No such Nick/channel\r\n"
#define ERR_NOSUCHSERVER(src, serv)							":" + src + " 402 " + serv + " :No such server\r\n"
#define ERR_NOSUCHCHANNEL(src, chan)						":" + src + " 403 " + chan + " :No such channel\r\n"
#define ERR_CANNOTSENDTOCHAN(src, chan)					":" + src + " 404 " + chan + " :Cannot send to channel\r\n" \
#define ERR_TOOMANYCHANNELS(src, chan)						":" + src + " 405 " + chan + " :You have joined too many channels\r\n"
#define ERR_NOTEXTTOSEND(src, nick)							":" + src + " 412 " + nick + " :No text to send\r\n"
#define ERR_INPUTTOOLONG(src, nick)							":" + src + " 417 " + nick + " :Input line too long\r\n"
#define ERR_UNKNOWNCOMMAND(src, cmd, nick)				":" + src + " 421 " + nick + " " + cmd + " :Uknown command\r\n"
#define ERR_NONICKNAMEGIVEN(src)								":" + src + " 431 :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(src, nick)					":" + src + " 432 " + nick + " :Erroneus nickname\r\n"
#define ERR_NICKNAMEINUSE(src, nick)						":" + src + " 433 " + nick + " :Nickname is already in use\r\n"
#define ERR_USERNOTINCHANNEL(src, nick, chan)			":" + src + " 441 " + nick + " " + chan + " :The user does not belong to this channel\r\n" 
#define ERR_NOTONCHANNEL(src, chan)							":" + src + " 442 " + chan + " :You're not on that channel\r\n"
#define ERR_USERONCHANNEL(src, nick, chan)				":" + src + " 443 " + nick + " " + chan + " :is already on channel\r\n"
#define ERR_NOTREGISTERED(src)								":" + src + " 451 :You have not registered\r\n"
#define ERR_ALREADYREGISTERED(src)							":" + src + " 462 :You may not reregister\r\n"
#define ERR_PASSWDMISMATCH(src)								":" + src + " 464 :Password incorrect\r\n"
#define ERR_CHANNELISFULL(src, chan)						":" + src + " 471 " + chan + " :Cannot join channel (+l)\r\n"
#define ERR_UKNOWNMODE(src, mode)							":" + src + " 472 " + mode + " :is unknown mode char to me\r\n"
#define ERR_INVITEONLYCHAN(src, chan)						":" + src + " 473 " + chan + " :Cannot join channel (+i)\r\n"
#define ERR_BADCHANNELKEY(src, chan)						":" + src + " 475 " + chan + " :Cannot join channel (+k)\r\n"
#define ERR_NOPRIVILIGES(src)									":" + src + " 481 :Permission denied- You're not an IRC operator\r\n"
#define ERR_CHANOPRIVSNEEDED(src, chan)					":" + src + " 482 " + chan + " :You're not channel operator\r\n"
#define ERR_UMODEUNKNOWNFLAG(src)							":" + src + " 501 :Unknown MODE flag\r\n"
#define ERR_USERDONTMATCH(src)								":" + src + " 502 :Cant change mode for other users\r\n"
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()