#pragma once

#include "../Command.h"
class PingCommand : public Command {
public:
	PingCommand();
	void execute(std::vector<std::string> args) override;
};