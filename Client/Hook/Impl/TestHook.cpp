#include "TestHook.h"
#include "../../Command/CommandManager.h"
#include "../../System.h"
#include "../../Event/Impl/TestEvent.h"
#include "../../Event/EventHandler.h"
#include "../../SDK/ItemRenderer.h"
#include "../../SDK/ItemStack.hpp"

double (__fastcall* TestO)(void*, void*, uint32_t, void*, float, float, float, float, float, int, bool, float);
double __fastcall Test_Callback(
	ItemRenderer* itemRenderer,
	void* renderContext,
	uint32_t itemRenderChunkType,
	ItemStack* item,
	float x,
	float y,
	float lightMultiplyer,
	float alphaMultiplyer,
	float scale,
	int frame,
	bool allowAnimation,
	float zOffset
) {
	auto i = item->getItem().get();
	if (i->getRawNameId() == std::string("splash_potion")) {
		*TestHook::color = mce::Color(0, 0, 255, 1);
		item->getItem().get()->setGlint(true);
	}
	else {
		*TestHook::color = TestHook::original;
	}
	auto result = TestO(itemRenderer, renderContext, itemRenderChunkType, item, x, y, lightMultiplyer, alphaMultiplyer, scale, frame, allowAnimation, zOffset);
	
	return result;
}

void TestHook::patch() {
	uintptr_t color = Mem::FindSig("F3 0F 10 15 ? ? ? ? 48 8D 8C 24 ? ? ? ? F3 0F 10 0D ? ? ? ? 45 8B C4");
	uintptr_t ref = color + 4;
	uintptr_t deref = *reinterpret_cast<uint32_t*>(ref);
	uintptr_t result = ref + deref + sizeof(uint32_t);
	this->color = reinterpret_cast<mce::Color*>(result);
	this->original = *this->color;
	this->autoPatch("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F9 45 8B E0", &Test_Callback, &TestO);
}

