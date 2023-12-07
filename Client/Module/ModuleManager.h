#pragma once

#include "Module.h"
#include <vector>
#include <iostream>

class ModuleManager {
public:
	std::vector<std::unique_ptr<Module>> modules;
	ModuleManager();
	template <class T> void addModule();
	template <class... Ts> void addModules();
};