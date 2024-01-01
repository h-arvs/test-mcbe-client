#pragma once
#include "../Module.h"

class TestEvent;
class TestModule : public Module {
public:
	TestModule();
	void onEnable() override;
	void onDisable() override;
	void onTestEvent(TestEvent&);
};