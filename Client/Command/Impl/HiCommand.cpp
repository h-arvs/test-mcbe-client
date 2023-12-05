#pragma once
#include "HiCommand.h"

void HiCommand::execute(std::vector<std::string> args) {
	std::string s = "hello";
	this->reply(s);
}

std::string_view HiCommand::getName() {
	return "hi";
}