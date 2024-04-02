#pragma once
#include <cstdint>
#include "Cancellable.h"

struct Short2 {
	short X;
	short Y;
};

enum class MouseButton {
	None = 0,
	Left = 1,
	Right = 2,
	Middle = 3,
	Scroll = 4
};

enum class MouseAction {
	Press,
	Release,
	ScrollUP,
	ScrollDOWN
};


class MouseInputEvent : public Cancellable {
	Short2 pos;
	Short2 movement;
	MouseButton button;
	MouseAction action;

	MouseAction fromChar(uint8_t c) {
		switch (c) {
		case 0: return MouseAction::Release;
		case 1: return MouseAction::Press;
		case 0x78: return MouseAction::ScrollUP;
		case 0x7F: return MouseAction::ScrollUP;
		case 0x80: return MouseAction::ScrollDOWN;
		case 0x88: return MouseAction::ScrollDOWN;
		}
	};

public:
	MouseInputEvent(char button, char action, short x, short y, short mX, short mY) {
		this->button = (MouseButton)button;
		this->action = fromChar(static_cast<uint8_t>(action));
		this->pos.X = x;
		this->pos.Y = y;
		this->movement.X = mX;
		this->movement.Y = mY;
	};

	MouseAction getAction() {
		return this->action;
	}

	MouseButton getButton() {
		return this->button;
	}

	Short2 getPos() {
		return this->pos;
	}

	Short2 getMovement() {
		return this->movement;
	}
};