#include "HookManager.h"
#include "Impl/PacketSendHook.h"

HookManager::HookManager() {
	MH_Initialize();
	this->addHook<PacketSendHook>();
}

template <class T>
bool HookManager::addHook() {
	this->hooks.push_back(std::make_unique<T>());
	return true;
}

bool HookManager::ApplyAll() {
	for (auto& a : this->hooks) {
		a->patch();
	}
	return true;
}

bool HookManager::UnApplyAll() {
	for (auto& a : this->hooks) {
		a->DisablePatch();
	}
	return true;
}

HookManager::~HookManager() {
	this->UnApplyAll();
	MH_Uninitialize();
}
