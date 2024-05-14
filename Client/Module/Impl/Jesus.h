#pragma once
#include "../Module.h"

class DoInWaterSensingEvent;
class AddShapesEvent;
class MoveInputComponent;
class Jesus : public Module {
public:
	Jesus();
	void onEnable() override;
	void onDisable() override;
	void onAddShapesEvent(AddShapesEvent&);
	void onInWaterCheck(DoInWaterSensingEvent&);
};