#include "ModuleManager.h"
#include "Impl/TestModule.h"
#include "Impl/ModuleInstanceComponent.h"

ModuleManager::ModuleManager() {
	this->addModules<
		TestModule
	>();
}

template <class T>
void ModuleManager::addModule() {
	auto moduleEntity = this->modules.create();
	this->modules.emplace<ModuleInstanceComponent>(moduleEntity, std::make_unique<T>());
}

template <class... Ts>
void ModuleManager::addModules() {
	(this->addModule<Ts>(), ...);
}