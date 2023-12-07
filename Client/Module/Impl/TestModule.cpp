#include "TestModule.h"

TestModule::TestModule() : Module("Test Module", "Module for testing") {

}

void TestModule::onEnable() {
	//enable callback
	printf("Enabled");
}

void TestModule::onDisable() {
	//disable callback
	printf("Disabled");
}