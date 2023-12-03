#include "System.h"

System* System::currentInstance = nullptr;
System::System() {
	System::currentInstance = this;
	this->commandManager = std::make_unique<CommandManager>();
	this->hookManager = std::make_unique<HookManager>();
}

System* System::tryGetSystem() {
	return System::currentInstance;
}

auto System::getCommandManager() -> CommandManager& {
	return *this->commandManager;
}

auto System::getHookManager() -> HookManager& {
	return *this->hookManager;
}