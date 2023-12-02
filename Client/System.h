#pragma once
#include "Command/CommandManager.h"
#include "Hook/HookManager.h"

class System {
	static System* currentInstance;
	std::unique_ptr<HookManager> hookManager = nullptr;
	std::unique_ptr<CommandManager> commandManager = nullptr;
public:
	System();
	static System* tryGetSystem();
	auto tryGetHookManager() -> std::unique_ptr<HookManager>&;
	auto tryGetCommandManager() -> std::unique_ptr<CommandManager>&;
};