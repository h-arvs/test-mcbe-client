#include "CIUpdateHook.h"
#include "../../Event/EventHandler.h"
#include "../../Event/Impl/CIUpdateEvent.h"

void(__fastcall* ClientInstanceUpdateO)(ClientInstance*);
void __fastcall ClientInstanceUpdateCallback(ClientInstance* ci) {
	ClientInstanceUpdateEvent e(ci);
	EventHandler<ClientInstanceUpdateEvent>::trigger(e);
	return ClientInstanceUpdateO(ci);
}

void CIUpdateHook::patch() {
	auto sig = "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 0F B6 F2";
	this->autoPatch(sig, &ClientInstanceUpdateCallback, &ClientInstanceUpdateO);
}

