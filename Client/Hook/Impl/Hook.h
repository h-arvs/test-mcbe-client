#pragma once
#include "../../../Utils/Mem.h"
#include <MinHook.h>

class HookManager;
class Hook {
	uintptr_t address;
public:
	virtual void patch() = 0;
	void AutoPatch(std::string_view sig, void* patch, void* old);
	void DisablePatch();
};