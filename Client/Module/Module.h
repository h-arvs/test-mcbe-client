#pragma once
#include <string>

class Module {
public:
	std::string name;
	std::string desc;
	bool enabled = false;
	Module(std::string name, std::string desc) : name(std::move(name)), desc(std::move(desc)) {};
	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};