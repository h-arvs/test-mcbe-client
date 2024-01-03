#include "TestModule.h"
#include "../../Event/Impl/TestEvent.h"

TestModule::TestModule() : Module("Test Module", "Module for testing") {
	
}

void TestModule::onEnable() {
	printf("Enabled");
	this->listen<TestEvent, &TestModule::onTestEvent>();
}

void TestModule::onDisable() {
	printf("Disabled");
	this->deafen<TestEvent>();
}

void TestModule::onTestEvent(TestEvent& e) {
	printf(e.val.c_str());
}