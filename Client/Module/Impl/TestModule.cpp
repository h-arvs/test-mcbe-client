#include "TestModule.h"
#include "../../Event/Impl/TestEvent.h"

TestModule::TestModule() : Module("Test Module", "Module for testing") {
	this->listen<TestEvent, &TestModule::onTestEvent>(this);
}

void TestModule::onEnable() {
	//enable callback
	printf("Enabled");
}

void TestModule::onDisable() {
	//disable callback
	printf("Disabled");
}

void TestModule::onTestEvent(TestEvent& event) {
	event.setVal("AAA");
}