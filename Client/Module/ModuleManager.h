#pragma once

#include "Module.h"
#include "../../Utils/Manager.h"

class ModuleManager : public Manager<Module> {
public:
	ModuleManager();
};