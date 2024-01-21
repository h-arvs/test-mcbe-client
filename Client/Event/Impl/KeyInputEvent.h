#pragma once
#include "Cancellable.h"

enum class Action {
	RELEASED,
	PRESSED
};

class KeyInputEvent : public Cancellable{
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