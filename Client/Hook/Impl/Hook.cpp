#include "Hook.h"

void Hook::AutoPatch(std::string_view sig, void* patch, void* old) {
	auto a = Mem::FindSig(sig);
	this->address = a;
	MH_CreateHook(reinterpret_cast<LPVOID*>(a), patch, (LPVOID*)old);
	MH_EnableHook(reinterpret_cast<LPVOID*>(a));
}

void Hook::DisablePatch() {
	MH_DisableHook(reinterpret_cast<LPVOID*>(this->address));
}

Hook::Hook() {
	
}