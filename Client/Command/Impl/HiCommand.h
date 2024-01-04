#pragma once

#include "../Command.h"
class HiCommand : public Command {
public:
	HiCommand();
	void execute(std::vector<std::string> args) override;
};