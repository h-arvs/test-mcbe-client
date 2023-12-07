#include "ModuleManager.h"
#include "Impl/TestModule.h"

ModuleManager::ModuleManager() {
	this->addModules<TestModule>();
}
template <class T>
void ModuleManager::addModule() {
	this->modules.push_back(std::make_unique<T>());
}

template <class... Ts>
void ModuleManager::addModules() {
	(this->addModule<Ts>(), ...);
}
