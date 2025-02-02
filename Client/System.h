#pragma once
#include "Command/CommandManager.h"
#include "Hook/HookManager.h"
#include "Module/ModuleManager.h"
#include "SDK/Game.h"

class System : public Listener{
	static System* currentInstance;
	std::unique_ptr<HookManager> hookManager = nullptr;
	std::unique_ptr<CommandManager> commandManager = nullptr;
	std::unique_ptr<ModuleManager> moduleManager = nullptr;
	std::unique_ptr<Game> game = nullptr;

	std::filesystem::path checkAndCreateStorage();
public:
	static constexpr std::string name = "TestClient";
	System();
	static System* tryGetSystem();
	auto getHookManager() -> HookManager&;
	auto getCommandManager() -> CommandManager&;
	auto getModuleManager() -> ModuleManager&;
	auto getGame() -> Game&;

	static std::string getStoragePath();
};