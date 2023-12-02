#pragma once
#include "HiCommand.h"

void HiCommand::execute(std::vector<std::string> args) {
	printf("Hello");
}

std::string_view HiCommand::getName() {
	return "Hi";
}