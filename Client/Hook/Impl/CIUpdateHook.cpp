#include "CIUpdateHook.h"

void(__fastcall* ClientInstanceUpdateO)(ClientInstance*);
void __fastcall ClientInstanceUpdateCallback(ClientInstance* ci) {
	System::tryGetSystem()->getGame().setClientInstance(ci);
	return ClientInstanceUpdateO(ci);
}

void CIUpdateHook::patch() {
	auto sig = "48 89 5c 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8d ac 24 ? ? ? ? 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 85 ? ? ? ? 44 0f b6 f2 48 8b f1";
	this->autoPatch(sig, &ClientInstanceUpdateCallback, &ClientInstanceUpdateO);
}

