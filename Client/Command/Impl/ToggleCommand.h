#pragma once
#include "../Command.h"

class ToggleCommand : public Command{
public:
	ToggleCommand();
	void execute(std::vector<std::string> args) override;
};