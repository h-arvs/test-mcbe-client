#pragma once
#include <iostream>
#include <vector>

class Command {
public:
	virtual void execute(std::vector<std::string> args) = 0;
	virtual std::string_view getName() = 0;
	void reply(std::string& msg) {
		System::tryGetSystem()->getCommandManager().reply(msg);
	};
};