#include "InWaterSensingSystemHook.h"
#include "../../Event/Impl/DoInWaterSensingEvent.h"
#include "../../Event/EventHandler.h"
#include "../../SDK/BlockSource.h"
#include "../../SDK/StrictEntityContext.h"

void(__fastcall* InWaterSensingSystemO)(StrictEntityContext&, void*, void*, void*, void*, void*, void*, void*);
void __fastcall InWaterSensingSystemCallback(StrictEntityContext& a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8) {
	DoInWaterSensingEvent e{a1.mEntity};
	EventHandler<DoInWaterSensingEvent>::trigger(e);
	if (e.isCancelled()) return;
	return InWaterSensingSystemO(a1, a2, a3, a4, a5, a6, a7, a8);
}

void InWaterSensingSystemHook::patch() {
	this->autoPatch("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 83 3A 05", &InWaterSensingSystemCallback, &InWaterSensingSystemO);
}