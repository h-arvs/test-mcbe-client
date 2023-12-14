#include "ModuleManager.h"
#include "Impl/TestModule.h"

ModuleManager::ModuleManager() {
	this->addItems<TestModule>();
}
