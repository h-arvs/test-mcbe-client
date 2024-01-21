#pragma once
#include "../Module.h"

class RenderEvent;
class MouseInputEvent;
class KeyInputEvent;

class ClickGui : public Module {
public:
	ClickGui();
	void onEnable() override;
	void onDisable() override;
	void onRender(RenderEvent&);
	void onKey(KeyInputEvent&);
	void onMouse(MouseInputEvent&);
};