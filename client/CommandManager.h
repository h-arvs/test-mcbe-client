#pragma once
#include "commands/Command.h"
#include <vector>

class CommandManager {
public:
	std::vector<std::shared_ptr<Command>> commands;
	CommandManager();
	template<class T> bool AddCommand();
};