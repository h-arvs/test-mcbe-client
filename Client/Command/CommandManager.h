#pragma once
#include "Impl/Command.h"
#include "../../Utils/Manager.h"

class CommandManager : public Manager<Command> {
public:
	std::string commandPrefix = "!";
	void executeCommand(std::string rawCommandString);
	std::unique_ptr<Command>& findCommand(std::string name);
	void reply(std::string&);
	CommandManager();
};