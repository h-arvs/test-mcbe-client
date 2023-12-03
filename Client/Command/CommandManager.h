#pragma once
#include "Impl/Command.h"
#include <vector>


class CommandManager {
	template<class T> bool addCommand();
public:
	std::string commandPrefix = "!";
	std::vector<std::unique_ptr<Command>> commands;
	void executeCommand(std::string rawCommandString);
	void reply(std::string&);
	CommandManager();
};