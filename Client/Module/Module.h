#pragma once
#include <string>
#include "../Event/Listener.h"

class Module : public Listener{
public:
	std::string name;
	std::string desc;
	bool enabled = false;
	Module(std::string name, std::string desc) : name(std::move(name)), desc(std::move(desc)) {};
	void setState(bool state) {
		if (this->enabled != state) {
			if (state == true) this->onEnable();
			else this->onDisable();
			this->enabled = state;
		}
	};
	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};