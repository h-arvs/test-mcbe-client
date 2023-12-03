#pragma once
#include "Impl\Hook.h"
#include <vector>
#include <iostream>

class HookManager {
	std::vector<std::unique_ptr<Hook>> hooks;
	template <class T> bool addHook();
public:
	HookManager();
	~HookManager();
	bool applyAll();
	bool unApplyAll();
};