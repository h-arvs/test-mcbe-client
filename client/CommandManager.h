#pragma once
#include "commands/Command.h"
#include <vector>

class CommandManager {
	template<class T> bool AddCommand();
	std::string commandPrefix = "!";
public:
	std::vector<std::unique_ptr<Command>> commands;
	void executeCommand(std::string rawCommandString);
	CommandManager();
};