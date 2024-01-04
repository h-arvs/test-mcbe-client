#pragma once
#include "PingCommand.h"
#include "../../System.h"

PingCommand::PingCommand() : Command({ "ping" }, "returns pong") {
}

void PingCommand::execute(std::vector<std::string> args) {
	for (auto s : args) {
		this->reply("pong");
	}
}
