#include "CommandManager.h"
#include "Impl/PingCommand.h"
#include "Impl/HiCommand.h"

CommandManager::CommandManager(){
	this->addCommand<PingCommand>();
	this->addCommand<HiCommand>();
}

template<class T>
bool CommandManager::addCommand() {
	this->commands.push_back(std::make_unique<T>());
	return true;
}

void CommandManager::executeCommand(std::string rawCommandString) {
	auto a = rawCommandString;
	a.erase(0, this->commandPrefix.length());
	auto splitArgs = std::vector<std::string>();
	std::string hold = " ";
	a += hold;
	auto pos = 0;

	while ((pos = a.find(" ")) != std::string::npos) {
		splitArgs.push_back(a.substr(0, pos));	
		a.erase(0, pos + hold.length());
	}

	for (auto& c : this->commands) {
		if (c->getName().rfind(splitArgs.at(0)) == 0) {
			splitArgs.erase(splitArgs.begin()); // remove command name from arg list
			return c->execute(splitArgs);
		}
	}
}

