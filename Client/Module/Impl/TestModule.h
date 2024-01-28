#pragma once
#include "../Module.h"

class ClientInstanceUpdateEvent;
class TestModule : public Module {
public:
	TestModule();
	void onEnable() override;
	void onDisable() override;
	void onUpdate(ClientInstanceUpdateEvent& e);
};