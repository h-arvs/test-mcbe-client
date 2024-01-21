#include "InputHooks.h"
#include "../../Event/Impl/KeyInputEvent.h"
#include "../../Event/Impl/MouseInputEvent.h"
#include "../../Event/EventHandler.h"
#include <imgui.h>

void(__fastcall* mouseHookO)(void*, char, char, short, short, short, short, bool);
void __fastcall mouseHookCallback(void* self, char button, char action, short mouseX, short mouseY, short movementX, short movementY, bool scroll) {
	if (ImGui::GetCurrentContext() == nullptr) return;
	ImGuiIO& io = ImGui::GetIO();
	if (button > 0 && button < 3) {
		io.AddMouseButtonEvent(button - 1, action);
	}
	if (button == 4) {
		io.AddMouseWheelEvent(0, static_cast<float>(action));
	}
	else {
		io.AddMousePosEvent(mouseX, mouseY);
	}

	MouseInputEvent e(button, action, mouseX, mouseY, movementX, movementY);
	EventHandler<MouseInputEvent>::trigger(e);
	if (e.isCancelled()) return;
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
	if (e.isCancelled()) return;
	return keyHookO(key, action);
}
void KeyBoardInputHook::patch() {
	this->autoPatch("48 83 ?? ?? 0F B6 ?? 4C 8D ?? ?? ?? ?? ?? ?? 54",
		&keyHooKCallback,
		&keyHookO
		);
}