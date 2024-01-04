#pragma once
#include <iostream>
#include <vector>


class Command {
public:
	std::vector<std::string> names;
	std::string desc;
	virtual void execute(std::vector<std::string> args) = 0;
	Command(std::vector<std::string> names, std::string desc) : names(std::move(names)), desc(std::move(desc)) {};
	void reply(std::string msg);
};