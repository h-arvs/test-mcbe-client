#include "InputHooks.h"
#include "../../Event/Impl/KeyInputEvent.h"
#include "../../Event/EventHandler.h"

void(__fastcall* mouseHookO)(void*, char, char, short, short, short, short, bool);
void __fastcall mouseHookCallback(void* self, char button, char action, short mouseX, short mouseY, short movementX, short movementY, bool scroll) {
	return mouseHookO(self, button, action, mouseX, mouseY, movementX, movementY, scroll);
}

void MouseInputHook::patch() {
	this->autoPatch("48 8B ?? ?? 89 ?? ?? ?? 89 ?? ?? ?? 89 ?? ?? 57 41 ?? 41 ?? 41 ?? 41 ?? 48 83 ?? ?? 44 ?? ?? ?? ?? ?? ?? ?? ?? 48",
		&mouseHookCallback, &mouseHookO);
}

void(__fastcall* keyHookO)(int, int);
void __fastcall keyHooKCallback(int key, int action) {
	KeyInputEvent e(key, action);
	EventHandler<KeyInputEvent>::trigger(e);
	return keyHookO(key, action);
}
void KeyBoardInputHook::patch() {
	this->autoPatch("48 83 ?? ?? 0F B6 ?? 4C 8D ?? ?? ?? ?? ?? ?? 54",
		&keyHooKCallback,
		&keyHookO
		);
}