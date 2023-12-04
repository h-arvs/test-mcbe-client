#pragma once
#include <iostream>
#include "Module.h"

struct ModuleInstanceComponent {
	std::unique_ptr<Module> instance = nullptr;
};