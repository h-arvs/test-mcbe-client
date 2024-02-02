#pragma once
#include <string>
#include "../Event/Listener.h"
#include "../Event/Impl/BindEvent.h"

class Module : public Listener{
	void onHotKey(BindEvent& e) {
		if (e.getKey() == this->hotkey && e.getAction() == Action::PRESSED) this->toggle();
	}
public:
	std::string name;
	std::string desc;
	int hotkey = 0;
	bool enabled = false;
	Module(std::string name, std::string desc) : name(std::move(name)), desc(std::move(desc)) {};

	void setState(bool state) {
		if (this->enabled != state) {
			if (state == true) this->onEnable();
			else this->onDisable();
			this->enabled = state;
		}
	};

	bool toggle() {
		this->setState(!this->enabled);
		return this->enabled;
	}

	void bind(int key) {
		this->hotkey = key;
		this->listen<BindEvent, &Module::onHotKey>();
	}

	void unbind() {
		this->hotkey = 0;
		this->deafen<BindEvent>();
	}

	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};