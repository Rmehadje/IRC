#include "../include/Bot.hpp"
#include "../include/Replies.hpp"
#include "../include/Server.hpp"

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
	"TOPIC:   <Channel> <TOPIC>,                       The TOPIC command serves the purpose of giving you the possibility of changing the Topic, or see the topic set for the channel\n"
	"KICK:    <Channel> <user>,                            The KICK command ejects a user from the Channel.\n"
	"INVITE:  <NickName> <Channel>,                 The INVITE command hands you the power of inviting your peers to the Channel.\n"
	"PRIVMSG: <target>   <message>,                 It is quite self explanatory, this command is used to send a private message to someone.\n\n"
	"MODE: this is used to change Channel modes, for this you would need to be the OP, here are the modes available:\n"
	"+i: #Channel <+i>                                         Set or remove the invite-only for the channel.\n"
	"+t: #Channel <+t>                                        Set or remove the Topic restrictions for the OP.\n"
	"+k: #Channel <+K> <PassWord>                 Set or remove Channel Password.\n"
	"+l: #Channel <+l> <int>                              Set or remove the limit of users in one Channel.\n"
	"+o: #Channel <+/-o> <NickName>            Set or remove the OP privilages to a user.\n\n"
	"As mentioned before, some of these commands require you to be the OP, you can't use KICK and MODE if you are a user, unless some restrtictions have been softened for you.";
	user->setBuffer(RPL_BOT_HC(user->getHostname(), Help));
}

void	Bot::BotCommands(Users *user){
	std::string Help = "If you would like to know what i can do, here is a list of my capabilities: \n"
	"User list: (write <BOT UL>) gives you all the users that are in the same server as you.\n"
	"Channel list: (write <BOT CL>), shows you all the available Channels created by you or other users.\n"
	"EightBall: (write <BOT Eightball>), you summon my capabilities of second sight by advising you wether you should, or should not act upon what you ask me.\n"
	"d20: (write <BOT d20>), permits you to test your luck out of 20.\n";
	user->setBuffer(RPL_BOT_BC(user->getHostname(), Help));
}

void	Bot::UserList(Users *user, std::vector<Users *>	&AllUsers){
	std::string Help = "here is the list for every user in the server:";
	for (std::vector <Users *>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++){
		Help += (*it)->getNickname();
		Help += " / ";
	}
		user->setBuffer(RPL_BOT_UL(Help));
}

void	Bot::ChannelList(Users *user, std::vector<Channel *> &AllChannels){
	std::string everychannel;
	if (AllChannels.empty()){
		everychannel = "There are no Channels available currently, feel free to create one!";
	}
	else{
		everychannel = "here is the list for every every channel in the server: ";
		for (std::vector<Channel *>::iterator it = AllChannels.begin(); it != AllChannels.end(); it++){
			everychannel += (*it)->getName();
			everychannel += " / ";
	}
	}
	user->setBuffer(RPL_BOT_CL(everychannel));
}

void	Bot::EightBall(Users *user){
    static const char* responses[] = {
   	"it appears so.",
   	"you'll learn from this.",
   	"it may not go as planned.",
   	"think further about it.",
   	"i wouldn't know.",
   	"i shouldn't say.",
   	"it is favorable.",
   	"perhaps another time.",
   	"guaranteed.",
   	"the time is right.",
   	"don't let that distract you.",
   	"you have other things to worry about.",
   	"very well.",
   	"there is a chance.",
   	"it could be done.",
   	"I would not do that.",
   	"doubtful.",
   	"no doubt in me.",
   	"maybe in another timeline.",
   	"It would mean farewell.",
   	"it would bring novelty.",
   	"Focus, and ask again when you know more."};

    const int num_responses = sizeof(responses) / sizeof(responses[0]);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, num_responses - 1);
    int random_index = dis(gen);
    std::string randomResponse = responses[random_index];
    user->setBuffer(RPL_BOT_EB(randomResponse));
}

void	Bot::d20(Users *user){
	std::random_device rd;
   std::mt19937 gen(rd());
	std::string str = "you have summoned the d20...";
   std::uniform_int_distribution<> dis(1, 20);
	int dice = dis(gen);
	str += std::to_string(dice);
	user->setBuffer(RPL_BOT_D20(str));
}

void	Bot::executeBot(Command cmd, Users *user, std::vector<Users *>users, std::vector<Channel *>Channels){
	if (cmd.Rest.find("Eightball") != std::string::npos)
	{
		int i = cmd.Rest.find(' ');
		cmd.Rest = cmd.Rest.substr(0, i);
	}
	if (cmd.Rest == "HELPC")
		HelpCommands(user);
	else if (cmd.Rest == "UL")
		UserList(user, users);
	else if (cmd.Rest == "d20")
		d20(user);
	else if (cmd.Rest == "Eightball")
		EightBall(user);
	else if (cmd.Rest == "CL")
		ChannelList(user, Channels);
	else if (cmd.Rest == "BOTC")
		BotCommands(user);
}