#include "System.h"

System* System::currentInstance = nullptr;
System::System() {
	System::currentInstance = this;
	this->moduleManager = std::make_unique<ModuleManager>();
	this->commandManager = std::make_unique<CommandManager>();
	this->game = std::make_unique<Game>();
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

auto System::getGame() -> Game& {
	return *this->game;
}

auto System::getModuleManager() -> ModuleManager& {
	return *this->moduleManager;
}