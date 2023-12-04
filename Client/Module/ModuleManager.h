#pragma once
#include <entt/entt.hpp>

class ModuleManager {
public:
	entt::registry modules;
	ModuleManager();
	template <class T>
	void addModule();
	template <class... Ts>
	void addModules();
};