#pragma once

#include "Command.h"
class PingCommand : public Command {
public:
	void execute() override;
};