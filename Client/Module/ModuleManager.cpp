#include "ModuleManager.h"
#include "Impl/CollisionEditor.h"
#include "Impl/ClickGui.h"
#include "Impl/Jesus.h"
#include "Impl/BlockEditor.h"

ModuleManager::ModuleManager() {
	auto render = this->addItem<Catagory>("Render");
	auto misc = this->addItem<Catagory>("Misc");
	render->addModules<ClickGui>();
	misc->addModules<
		CollisionEditor,
		Jesus,
		BlockEditor
	>();
}
