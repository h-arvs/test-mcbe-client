#pragma once
#include "../Module.h"
#include "../../Event/Impl/KeyInputEvent.h"

class AddShapesEvent;
class Jesus : public Module {
	Action shift = Action::RELEASED;
public:
	Jesus();
	void onEnable() override;
	void onDisable() override;
	void onAddShapesEvent(AddShapesEvent&);
	void onKey(KeyInputEvent&);
};