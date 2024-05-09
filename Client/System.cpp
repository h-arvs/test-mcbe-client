#include "System.h"
#include "../Utils/MiscUtil.h"
#include <filesystem>

System* System::currentInstance = nullptr;
System::System() {

	this->checkAndCreateStorage();

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

void System::checkAndCreateStorage() {
	std::filesystem::path path = MiscUtil::GetRoamingState() + "\\" + this->name;
	if (!std::filesystem::exists(path)) std::filesystem::create_directory(path);
}
