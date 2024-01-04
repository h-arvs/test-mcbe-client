#pragma once
#include "HiCommand.h"

HiCommand::HiCommand() : Command({"hi", "hello"}, "returns hello") {

}

void HiCommand::execute(std::vector<std::string> args) {
	this->reply("hello");
}