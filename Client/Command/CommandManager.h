#pragma once
#include "Impl/Command.h"
#include <vector>
#include <iostream>

class CommandManager {
	template<class T> bool addCommand();
	template <class... Ts> void addCommands();
	std::vector<std::unique_ptr<Command>> commands;
public:
	std::string commandPrefix = "!";
	void executeCommand(std::string rawCommandString);
	std::unique_ptr<Command>& findCommand(std::string name);
	void reply(std::string&);
	CommandManager();
};