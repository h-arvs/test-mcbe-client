#pragma once
#include "../Module.h"

class TestModule : public Module {
public:
	TestModule();
	void onEnable() override;
	void onDisable() override;
};