#include "TestModule.h"
#include "../../Event/Impl/CIUpdateEvent.h"

TestModule::TestModule() : Module("Test Module", "Module for testing") {
	
}

void TestModule::onEnable() {
	printf("Enabled");
	this->listen<ClientInstanceUpdateEvent, &TestModule::onUpdate>();
}

void TestModule::onDisable() {
	printf("Disabled");
	this->deafen<ClientInstanceUpdateEvent>();
}

void TestModule::onUpdate(ClientInstanceUpdateEvent& e) {
	auto ci = e.getClientInstance();
	auto lp = ci->getClientPlayer();
	auto d = lp->getdimension();
	auto bs = d->getblockSource();
	auto cs = d->getchunkSource();
	printf("", bs, cs);
}