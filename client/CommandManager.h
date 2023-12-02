#pragma once
#include "commands/Command.h"
#include <vector>

enum CommandManagerResult {
	COMMAND_NOT_FOUND,
	COMMAND_EXECUTED,
	COMMAND_FAILED,
	CONTINUE
};
class CommandManager {
	template<class T> bool AddCommand();
	std::string commandPrefix = "!";
public:
	std::vector<std::unique_ptr<Command>> commands;
	void executeCommand(std::string rawCommandString);
	CommandManager();
};