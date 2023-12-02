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

auto System::tryGetCommandManager() -> std::unique_ptr<CommandManager>& {
	return this->commandManager;
}

auto System::tryGetHookManager() ->std::unique_ptr<HookManager>& {
	return this->hookManager;
}