#pragma once

//error replies

#define RPL_WELCOME(src, user, host, nick)				":" + src + " 001 " + "Welcome to the IRC_server network " nick "." + user + "@" + host + "/r/n"
#define RPL_UMODEIS(src, nick, mode)						":" + src + " 221 " + nick + " " + mode + "/r/n"
#define RPL_LUSERUNKNOWN()
#define ERR_NOSUCHNICK(src, nick, chan)					":" + src + " 401 " + nick + " " + chan + " :No such Nick/channel/r/n"
#define ERR_NOSUCHSERVER(src, serv)							":" + src + " 402 " + serv + " :No such server/r/n"
#define ERR_NOSUCHCHANNEL(src, chan)						":" + src + " 403 " + nick + " " + chan + " :No such channel/r/n"
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
#define ERR_()
