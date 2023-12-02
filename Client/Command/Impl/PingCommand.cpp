#pragma once
#include "PingCommand.h"

void PingCommand::execute(std::vector<std::string> args) {
	for (auto s : args) {
		printf(s.c_str());
		printf("\n");
	}
}

std::string_view PingCommand::getName() {
	return "ping";
}