#pragma once
#include "Impl/Command.h"
#include <vector>
#include "entt/entt.hpp"


class CommandManager {
	template<class T> bool addCommand();
	template <class... Ts> void addCommands();
public:
	std::string commandPrefix = "!";
	entt::registry commands;
	void executeCommand(std::string rawCommandString);
	void reply(std::string&);
	CommandManager();
};