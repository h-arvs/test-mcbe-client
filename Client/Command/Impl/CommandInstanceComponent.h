#pragma once

#include "Command.h"

struct CommandInstanceComponent {
	std::unique_ptr<Command> instance = nullptr;
};