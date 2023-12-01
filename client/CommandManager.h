#pragma once
#include "commands/Command.h"
#include <vector>

class CommandManager {
	template<class T> bool AddCommand();
public:
	std::vector<std::unique_ptr<Command>> commands;
	CommandManager();
};