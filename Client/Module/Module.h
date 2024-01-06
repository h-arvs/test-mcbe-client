#pragma once
#include <string>
#include "../Event/Listener.h"
#include "../Event/Impl/KeyInputEvent.h"

class Module : public Listener{
public:
	std::string name;
	std::string desc;
	int hotkey = NULL;
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
		this->listen<KeyInputEvent, &Module::onKey>();
	}

	void unbind() {
		this->hotkey = NULL;
		this->deafen<KeyInputEvent>();
	}

	void onKey(KeyInputEvent& e) {
		if (e.getKey() == this->hotkey && e.getAction() == Action::PRESSED) this->toggle();
	}

	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};