#include "CommandManager.h"
#include "Impl/PingCommand.h"
#include "Impl/HiCommand.h"
#include "../System.h"

CommandManager::CommandManager(){
	this->addCommands<
		PingCommand,
		HiCommand
	>();
}

template<class T>
bool CommandManager::addCommand() {
	this->commands.push_back(std::make_unique<T>());
	return true;
}

template <class... Ts>
void CommandManager::addCommands() {
	(this->addCommand<Ts>(), ...);
}

std::unique_ptr<Command>& CommandManager::findCommand(std::string name) {
	for (auto& instance : this->commands) {
		if (instance->getName() == name) {
			return instance;
		}
	}
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

	auto& instance = this->findCommand(splitArgs.at(0));
	if (instance != nullptr) {
		splitArgs.erase(splitArgs.begin()); // remove command name from arg list
		return instance->caughtExecute(splitArgs);
	}
	
	return executeResult::COMMANDNOTFOUND;
}

void CommandManager::reply(std::string& msg) {
	System::tryGetSystem()->getGame().getClientInstance()->getGuiData()->displayMessage(msg);
}

