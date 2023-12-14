#pragma once
#include "Impl\Hook.h"
#include "../../Utils/Manager.h"

class HookManager : public Manager<Hook> {
public:
	HookManager();
	~HookManager();
	bool applyAll();
	bool unApplyAll();
};