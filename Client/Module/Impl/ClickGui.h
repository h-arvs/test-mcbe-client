#pragma once
#include "../Module.h"

class RenderEvent;
class ClickGui : public Module {
public:
	ClickGui();
	void onEnable() override;
	void onDisable() override;
	void onRender(RenderEvent&);
};