#pragma once
#include "Command/CommandManager.h"
#include "Hook/HookManager.h"
#include "SDK/Game.h"

class System {
	static System* currentInstance;
	std::unique_ptr<HookManager> hookManager = nullptr;
	std::unique_ptr<CommandManager> commandManager = nullptr;
	std::unique_ptr<Game> game = nullptr;
public:
	System();
	static System* tryGetSystem();
	auto getHookManager() -> HookManager&;
	auto getCommandManager() -> CommandManager&;
	auto getGame() -> Game&;
};