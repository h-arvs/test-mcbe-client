#pragma once

#include "Command.h"
class PingCommand : public Command {
public:
	void execute(std::vector<std::string> args) override;
	std::string_view getName() override;
};