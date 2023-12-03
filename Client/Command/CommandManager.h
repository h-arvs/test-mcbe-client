#pragma once
#include "Impl/Command.h"
#include <vector>

class CommandManager {
	template<class T> bool addCommand();
	std::string commandPrefix = "!";
public:
	std::vector<std::unique_ptr<Command>> commands;
	void executeCommand(std::string rawCommandString);
	CommandManager();
};