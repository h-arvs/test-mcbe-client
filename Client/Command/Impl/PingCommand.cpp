#pragma once
#include "PingCommand.h"
#include "../../System.h"

void PingCommand::execute(std::vector<std::string> args) {
	for (auto s : args) {
		this->reply(s);
	}
}

std::string_view PingCommand::getName() {
	return "ping";
}