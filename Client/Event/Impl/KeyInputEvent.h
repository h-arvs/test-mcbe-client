#pragma once

enum class Action {
	RELEASED,
	PRESSED
};

class KeyInputEvent {
	int key;
	Action action;
public:
	KeyInputEvent(int key, int action) {
		this->key = key;
		this->action = (Action)action;
	}
	
	int getKey() {
		return this->key;
	}

	Action getAction() {
		return this->action;
	}
};