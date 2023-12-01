#include "CommandManager.h"
#include "commands/PingCommand.h"
#include "commands/HiCommand.h"

CommandManager::CommandManager() {
	this->AddCommand<PingCommand>();
	this->AddCommand<HiCommand>();
}

template<class T>
bool CommandManager::AddCommand() {
	commands.push_back(std::make_shared<T>());
	return true;
}