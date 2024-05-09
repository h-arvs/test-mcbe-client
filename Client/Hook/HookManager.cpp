#include "HookManager.h"
#include "Impl/PacketSendHook.h"
#include "Impl/CIUpdateHook.h"
#include "Impl/DXHook.h"
#include "Impl/InputHooks.h"
#include "Impl/AddShapesHook.h"
#include "Impl/InWaterSensingSystemHook.h"
#include "Impl/TestHook.h"

HookManager::HookManager() {
	MH_Initialize();
	this->addItems<
		DirectXHook,
		CIUpdateHook,
		PacketSendHook,
		KeyBoardInputHook,
		MouseInputHook,
		AddShapesHook,
		InWaterSensingSystemHook
		// TestHook
	>();
}

bool HookManager::applyAll() {
	for (auto& a : this->items) {
		a->patch();
	}
	printf("Patched");
	return true;
}

bool HookManager::unApplyAll() {
	printf("UnPatched");
	for (auto& a : this->items) {
		a->disablePatch();
	}
	return true;
}

HookManager::~HookManager() {
	this->unApplyAll();
	MH_Uninitialize();
}
