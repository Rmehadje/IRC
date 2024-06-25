#include "../include/Bot.hpp"
#include "../include/Replies.hpp"

Bot::Bot(std::string name){
	name = "The knight";
}

Bot::~Bot() {}

Bot::Bot(const Bot &cp){
	if (this != &cp){
		setBotName(cp.getBotName());
	}
}

Bot &Bot::operator=(const Bot &og){
	if (this != &og){
		setBotName(og.getBotName());
	}
	return (*this);
}

void	Bot::setBotName(std::string name){
	this->name = name;
}
std::string	Bot::getBotName() const{
	return (this->name);
}

// void	Bot::Greetings(Users *user, Channel *channel)
// {
// 	std::cout << "Good folks, allow me to introduce " << user->getNickname() << " to our gathering here in "<< channel->getName() << "let us ensure they are made to feel like home within our noble walls." << std::endl; 
// }

void	Bot::HelpCommands(Users *user){
	std::string Help = "You ask and you shall receive, here is the list of commands:\n\n"
	"TOPIC: 	 <Channel>  <TOPIC>,   the TOPIC command serves the purpose of giving you the possibility of changing the Topic, or see the topic set for the channel\n"
	"KICK:  	 <Channel>  <user>, 	  the KICK command ejects a user from the Channel.\n"
	"INVITE:  <NickName> <Channel>, the INVITE command hands you the power of inviting your peers to the Channel.\n"
	"PRIVMSG: <target>   <message>, It is quite self explanatory, this command is used to send a private message to someone.\n\n"
	"MODE: this is used to change Channel modes, for this you would need to be the OP, here are the modes available:\n"
	"		+i: #Channel <+i>						set or remove the invite-only for the channel.\n"
	"		+t: #Channel <+t>						set or remove the Topic restrictions for the OP.\n"
	"		+k: #Channel <+K> <PassWord>					set or remove Channel Password.\n"
	"		+l: #Channel <+l> <int>						set or remove the limit of users in one Channel.\n"
	"		+o: #Channel <+/-o> <NickName>					set or remove the OP privilages to a user.\n\n"
	"As mentioned before, some of these commands require you to be the OP, you can't use KICK and MODE if you are a user, unless some restrtictions have been softened for you.";
	user->setBuffer(RPL_BOT_HC(user->getHostname(), Help));
}

// void	Bot::BotCommands(Users *user){
// 	std::cout << "If you would like to know what i can do, here is a list of my capabilities: " << std::endl;
// 	std::cout << "User list: (write UL) gives you all the users that are in the same server as you." << std::endl;
// 	std::cout << "Channel list: (write CL), shows you all the available Channels created by you or other users." << std::endl;
// 	std::cout << "EightBall : (write Eightball), you summon my capabilities of second sight by advising you wether you should, or should not act upon what you ask me." << std::endl;
// 	std::cout << "d20: (write d20), permits you to test your luck out of 20." << std::endl;
// }

// void	Bot::UserList(Users *user, std::vector<Users *>	&AllUsers){
// 	std::cout << "here is the list for every user in the server:" << std::endl;
// 	for (std::vector <Users *>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++){
// 		std::cout << (*it)->getNickname() << std::endl;
// 	}
// }

// void	Bot::ChannelList(Users *user, std::vector<Channel *> &AllChannels){
// 	if (AllChannels.empty()){
// 		std::cout << "There are no Channels available currently, feel free to create one!" << std::endl;
// 	}
// 	else{
// 		std::cout << "here is the list for every every channel in the server:" << std::endl;
// 		for (std::vector<Channel *>::iterator it = AllChannels.begin(); it != AllChannels.end(); it++){
// 			std::cout << (*it)->getName() << std::endl;
// 	}
// 	}
// }

// void	Bot::EightBall(Users *user){
// 	std::vector<std::string> responses = {
// 		"it appears so.",
// 		"you'll learn from this.",
// 		"it may not go as planned.",
// 		"think further about it.",
// 		"i wouldn't know.",
// 		"i shouldn't say.",
// 		"it is favorable.",
// 		"perhaps another time.",
// 		"guarenteed.",
// 		"the time is right.",
// 		"don't let that distract you.",
// 		"you have other things to worry about.",
// 		"very well.",
// 		"there is a chance.",
// 		"it could be done.",
// 		"I would not do that.",
// 		"doubtful.",
// 		"no doubt in me.",
// 		"maybe in another timeline.",
// 		"It would mean farewell.",
// 		"it would bring novelty.",
// 		"Focus, and ask again when you know more.",};
// 		std::random_device rd;
//       std::mt19937 gen(rd());
//       std::uniform_int_distribution<> dis(0, 21);
// 		std::vector<std::string>::iterator it = responses.begin();
// 		std::advance(it, dis(gen));
// }

// void	Bot::d20(Users *user){
// 	std::random_device rd;
//    std::mt19937 gen(rd());
// 	std::cout << "you have summoned the d20..." << std::endl;
//    std::uniform_int_distribution<> dis(0, 19);
// 	std::cout << dis(gen) << std::endl;
// }

void	Bot::executeBot(Command cmd, Users *user){
// 	if (cmd.Rest == "d20")
// 		d20(user);
// 	else if (cmd.Rest == "Eightball")
// 		EightBall(user);
// 	else if (cmd.Rest == "CL")
// 		ChannelList(user, getVectorCh());
// 	else if (cmd.Rest == "UL")
// 		UserList(user, getVectorU());
	if (cmd.Rest == "HELPC")
		HelpCommands(user);
// 	else if (cmd.Rest == "BOTC")
// 		BotCommands(user);
}