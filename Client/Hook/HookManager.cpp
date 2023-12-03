#include "HookManager.h"
#include "Impl/PacketSendHook.h"
#include "Impl/CIUpdateHook.h"

HookManager::HookManager() {
	MH_Initialize();
	this->addHook<PacketSendHook>();
	this->addHook<CIUpdateHook>();
}

template <class T>
bool HookManager::addHook() {
	this->hooks.push_back(std::make_unique<T>());
	return true;
}

bool HookManager::applyAll() {
	for (auto& a : this->hooks) {
		a->patch();
	}
	printf("Patched");
	return true;
}

bool HookManager::unApplyAll() {
	printf("UnPatched");
	for (auto& a : this->hooks) {
		a->disablePatch();
	}
	return true;
}

HookManager::~HookManager() {
	this->unApplyAll();
	MH_Uninitialize();
}
