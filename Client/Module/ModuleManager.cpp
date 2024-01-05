#include "ModuleManager.h"
#include "Impl/TestModule.h"
#include "Impl/ClickGui.h"

ModuleManager::ModuleManager() {
	auto render = this->addItem<Catagory>("Render");
	auto misc = this->addItem<Catagory>("Misc");
	render->addModules<ClickGui>();
	misc->addModules<TestModule>();
}
