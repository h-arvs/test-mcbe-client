#include "ModuleManager.h"
#include "Impl/TestModule.h"

ModuleManager::ModuleManager() {
	this->addModules<TestModule>();
}
