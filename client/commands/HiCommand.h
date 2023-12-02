#pragma once

#include "Command.h"
class HiCommand : public Command {
public:
	void execute(std::vector<std::string> args) override;
	std::string getName() override;
};