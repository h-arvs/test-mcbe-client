#include "ModuleManager.h"
#include "Impl/TestModule.h"

ModuleManager::ModuleManager() {
	auto testCatagory = this->addItem<Catagory>("Test Catagory");
	testCatagory->addModules<TestModule>();
}
