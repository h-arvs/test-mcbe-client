#pragma once
#include "../Module.h"

class AddShapesEvent;
class Jesus : public Module {
public:
	Jesus();
	void onEnable() override;
	void onDisable() override;
	void onAddShapesEvent(AddShapesEvent&);
};